//
// Created by zhaohe on 19-5-24.
//

#ifndef ZTIMECPP_BACKWARD_HELPER_HPP
#define ZTIMECPP_BACKWARD_HELPER_HPP
#include "../utils/backward/backward.hpp"
#include <string>
#include <sstream>

static inline std::string getStackInfo(int level = 32){
	backward::StackTrace st;
	st.load_here(level);
	backward::Printer p;
	p.object = true;
	p.snippet = true;
	p.color_mode = backward::ColorMode::always;
	p.address = true;

	std::ostringstream out;
	p.print(st, out);
	return out.str();
}

#endif //ZTIMECPP_BACKWARD_HELPER_HPP
