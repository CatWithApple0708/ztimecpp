//
// Created by zhaohe on 19-5-30.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>

#define GET_METHOD(var) \
	const __typeof__(var) &get##var() const { return var; }
#define SET_METHOD(var) \
	void set##var(const __typeof__(var) &value) { var = value; }

#define DATA1(v1)                                        \
	const __typeof__(v1) &get##v1() const { return v1; } \
	void set##v1(const __typeof__(v1) &value) { v1 = value; }

#define DATA2(v1, v2)                                         \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; }

#define DATA3(v1, v2, v3)                                     \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; }

#define DATA4(v1, v2, v3, v4)                                 \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; }

#define DATA5(v1, v2, v3, v4, v5)                             \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; } \
	const __typeof__(v5) &get##v5() const { return v5; }      \
	void set##v5(const __typeof__(v5) &value) { v5 = value; }

#define DATA6(v1, v2, v3, v4, v5, v6)                         \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; } \
	const __typeof__(v5) &get##v5() const { return v5; }      \
	void set##v5(const __typeof__(v5) &value) { v5 = value; } \
	const __typeof__(v6) &get##v6() const { return v6; }      \
	void set##v6(const __typeof__(v6) &value) { v6 = value; }

#define DATA7(v1, v2, v3, v4, v5, v6, v7)                     \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; } \
	const __typeof__(v5) &get##v5() const { return v5; }      \
	void set##v5(const __typeof__(v5) &value) { v5 = value; } \
	const __typeof__(v6) &get##v6() const { return v6; }      \
	void set##v6(const __typeof__(v6) &value) { v6 = value; } \
	const __typeof__(v7) &get##v7() const { return v7; }      \
	void set##v7(const __typeof__(v7) &value) { v7 = value; }

#define DATA8(v1, v2, v3, v4, v5, v6, v7, v8)                 \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; } \
	const __typeof__(v5) &get##v5() const { return v5; }      \
	void set##v5(const __typeof__(v5) &value) { v5 = value; } \
	const __typeof__(v6) &get##v6() const { return v6; }      \
	void set##v6(const __typeof__(v6) &value) { v6 = value; } \
	const __typeof__(v7) &get##v7() const { return v7; }      \
	void set##v7(const __typeof__(v7) &value) { v7 = value; } \
	const __typeof__(v8) &get##v8() const { return v8; }      \
	void set##v8(const __typeof__(v8) &value) { v8 = value; }

#define DATA9(v1, v2, v3, v4, v5, v6, v7, v8, v9)             \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; } \
	const __typeof__(v5) &get##v5() const { return v5; }      \
	void set##v5(const __typeof__(v5) &value) { v5 = value; } \
	const __typeof__(v6) &get##v6() const { return v6; }      \
	void set##v6(const __typeof__(v6) &value) { v6 = value; } \
	const __typeof__(v7) &get##v7() const { return v7; }      \
	void set##v7(const __typeof__(v7) &value) { v7 = value; } \
	const __typeof__(v8) &get##v8() const { return v8; }      \
	void set##v8(const __typeof__(v8) &value) { v8 = value; } \
	const __typeof__(v9) &get##v9() const { return v9; }      \
	void set##v9(const __typeof__(v9) &value) { v9 = value; }

#define DATA10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)       \
	const __typeof__(v1) &get##v1() const { return v1; }      \
	void set##v1(const __typeof__(v1) &value) { v1 = value; } \
	const __typeof__(v2) &get##v2() const { return v2; }      \
	void set##v2(const __typeof__(v2) &value) { v2 = value; } \
	const __typeof__(v3) &get##v3() const { return v3; }      \
	void set##v3(const __typeof__(v3) &value) { v3 = value; } \
	const __typeof__(v4) &get##v4() const { return v4; }      \
	void set##v4(const __typeof__(v4) &value) { v4 = value; } \
	const __typeof__(v5) &get##v5() const { return v5; }      \
	void set##v5(const __typeof__(v5) &value) { v5 = value; } \
	const __typeof__(v6) &get##v6() const { return v6; }      \
	void set##v6(const __typeof__(v6) &value) { v6 = value; } \
	const __typeof__(v7) &get##v7() const { return v7; }      \
	void set##v7(const __typeof__(v7) &value) { v7 = value; } \
	const __typeof__(v8) &get##v8() const { return v8; }      \
	void set##v8(const __typeof__(v8) &value) { v8 = value; } \
	const __typeof__(v9) &get##v9() const { return v9; }      \
	void set##v9(const __typeof__(v9) &value) { v9 = value; } \
	const __typeof__(v10) &get##v10() const { return v10; }   \
	void set##v10(const __typeof__(v10) &value) { v10 = value; }

// const __typeof__(v11) &get##v11() const { return v11; } void set##v11(const __typeof__(v11) &value) { v11 = value; }
// const __typeof__(v12) &get##v12() const { return v12; } void set##v12(const __typeof__(v12) &value) { v12 = value; }
// const __typeof__(v13) &get##v13() const { return v13; } void set##v13(const __typeof__(v13) &value) { v13 = value; }
// const __typeof__(v14) &get##v14() const { return v14; } void set##v14(const __typeof__(v14) &value) { v14 = value; }
// const __typeof__(v15) &get##v15() const { return v15; } void set##v15(const __typeof__(v15) &value) { v15 = value; }
// const __typeof__(v16) &get##v16() const { return v16; } void set##v16(const __typeof__(v16) &value) { v16 = value; }
// const __typeof__(v17) &get##v17() const { return v17; } void set##v17(const __typeof__(v17) &value) { v17 = value; }
// const __typeof__(v18) &get##v18() const { return v18; } void set##v18(const __typeof__(v18) &value) { v18 = value; }
// const __typeof__(v19) &get##v19() const { return v19; } void set##v19(const __typeof__(v19) &value) { v19 = value; }
// const __typeof__(v20) &get##v20() const { return v20; } void set##v20(const __typeof__(v20) &value) { v20 = value; }
