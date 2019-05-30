//
// Created by zhaohe on 19-5-30.
//

#pragma once
#include <memory>

/**
 * WARNING:
 * c++中所有的强转操作,效率都是比较低的,所以推荐代码写法如下:
 * bad
 * {
 * 		if(dpc<Type>(v)){
 *			dpc<Type>(v)->callFunc();
 *			dpc<Type>(v)->callFunc();
 * 		}
 * }
 * good
 * {
 * 		if(dpc<Type>(v)){
 * 			shared_ptr<Type> tmp = dpc<Type>(v);
 *			tmp->callFunc();
 *			tmp->callFunc();
 * 		}
 *
 * 		or:
 *
 * 		if(instanceof<Type>(v)){
 * 			shared_ptr<Type> tmp = dpc<Type>(v);
 *			tmp->callFunc();
 *			tmp->callFunc();
 * 		}
 * }
 *
 */
/**
 * shared<BaseType> var = make_shared<FatherType>();
 * if(dpc<FatherType>(var)){
 * 		//DoSomeThings
 * }
 */
#define dpc dynamic_pointer_cast

/**
 * Usage 1
 * BaseType* var = new FatherType;
 * if(dc<FatherType*>(var)){
 * 		//DoSomeThings
 * }
 *
 * Usage 2
 *
 * BaseType& var = FatherType();
 * if (dc<FatherType&>(var)){
 *
 * }
 *
 */
#define dc dynamic_cast

namespace zwsd {
template<typename T, typename Base>
static inline bool instanceof(const Base *ptr) {
	return dynamic_cast<const T *>(ptr) != nullptr;
}

template<typename T, typename Base>
static inline bool instanceof(const std::shared_ptr<Base> &ptr) {
	return std::dynamic_pointer_cast<T>(ptr) != nullptr;
}

template<typename T, typename Base>
static inline bool instanceof(const Base &val) {
	//之所以写这个检测,是因为不确定不同的编译器的行为会不会导致原本应该匹配上bool instanceof (const std::shared_ptr<Base> &ptr), 匹配到了这个方法
	//或者由于误删除bool instanceof (const std::shared_ptr<Base> &ptr),导致匹配上了这个方法.
	static_assert(std::is_base_of<Base, T>::value, "instanceof type T must be a class deriverd from Base");
	return typeid(T) == typeid(val);
}
}
