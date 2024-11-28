#pragma once
#ifndef util_h
#define util_h

#include <vector>
#include <list>
#include "IanFrustum.h"


namespace util
{
	class frustum_sectioning_lookup_2d;
	extern frustum_sectioning_lookup_2d fLookup;

	class frustum_sectioning_lookup_2d
	{
	public:
		frustum_sectioning_lookup_2d();
		~frustum_sectioning_lookup_2d();

		std::list<dims::IanFrustum> divideFrustumY(dims::IanFrustum startFrustum, std::list<int>& blockedIndex);
		std::list<dims::IanFrustum> divideFrustumX(dims::IanFrustum startFrustum, std::list<int>& blockedIndex);
		std::list<dims::IanFrustum> divideFrustumZ(dims::IanFrustum startFrustum, std::list<int>& blockedIndex);
	};
}

#endif
