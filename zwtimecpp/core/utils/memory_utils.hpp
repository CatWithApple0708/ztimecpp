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
#define zwdc dynamic_cast

namespace zwsd {
template <typename T, typename Base>
static inline bool instanceof (const Base *ptr) {
  return dynamic_cast<const T *>(ptr) != nullptr;
}

template <typename T, typename Base>
static inline bool instanceof (const std::shared_ptr<Base> &ptr) {
  return std::dynamic_pointer_cast<T>(ptr) != nullptr;
}

template <typename T, typename Base>
static inline bool instanceof (const Base &val) {
  //之所以写这个检测,是因为不确定不同的编译器的行为会不会导致原本应该匹配上bool
  //instanceof (const std::shared_ptr<Base> &ptr), 匹配到了这个方法
  //或者由于误删除bool instanceof (const std::shared_ptr<Base>
  //&ptr),导致匹配上了这个方法.
  static_assert(std::is_base_of<Base, T>::value,
                "instanceof type T must be a class deriverd from Base");
  return typeid(T) == typeid(val);
}
}  // namespace zwsd

namespace zwsd {
namespace core {
template <typename T>
weak_ptr<T> toWeak(shared_ptr<T> ptr) {
  weak_ptr<T> value = ptr;
  return value;
};
template <typename T>
shared_ptr<T> toShare(weak_ptr<T> v) {
  return v.lock();
}

template <typename T>
static inline T *zmemcpy(T *des, const T *src, size_t s) {
  return static_cast<T *>(::memcpy(
      static_cast<void *>(des), static_cast<const void *>(src), s * sizeof(T)));
}

template <typename T>
static inline T *zmemcpy(T *des, T *src, size_t s) {
  return static_cast<T *>(::memcpy(static_cast<void *>(des),
                                   static_cast<void *>(src), s * sizeof(T)));
}

template <typename T>
static inline T *zmemset(T *des, int c, size_t s) {
  return static_cast<T *>(::memset(static_cast<void *>(des), c, s * sizeof(T)));
}

/**
 * @brief  给const类型的变量赋值，注意此功能只可以在测试代码中使用
 * @note
 * @param  *v:
 * @param  value:
 * @retval
 */
template <typename T>
static inline void zAssignToConst(const T *v, T value) {
  (*(T *)(v)) = value;
}
/**
 * @brief
 * 拷贝数据到数组，注意有小数据类型向大数据类型拷贝的时候，如果数据长度并非整数倍，会造成数据丢失
 * @note
 * @param  &v:
 * @param  *data:
 * @param  data_size:
 * @retval None
 */
template <typename T, typename T2>
static inline void zAssignToVector(vector<T> &v, const T2 *data,
                                   size_t data_size) {
  static_assert(sizeof(T) % sizeof(T2) == 0 || sizeof(T2) % sizeof(T) == 0,
                "T 必须是T2的整数倍的size 或者T2是T的整数倍的size");
  size_t t1size = sizeof(T2) * data_size / sizeof(T);
  v.reserve(t1size);
  v.resize(t1size);
  zmemcpy(&v[0], (T *)data, t1size);
}
}  // namespace core
}  // namespace zwsd
