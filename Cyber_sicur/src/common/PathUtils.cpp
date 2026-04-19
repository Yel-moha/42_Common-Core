#include "common/PathUtils.hpp"

#include <filesystem>

namespace common
{
	std::string joinPaths(const std::string &base, const std::string &relative)
	{
		if (base.empty())
			return relative;
		if (relative.empty())
			return base;
		std::filesystem::path path(base);
		path /= relative;
		return path.lexically_normal().generic_string();
	}
}
