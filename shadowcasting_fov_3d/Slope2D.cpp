#include "Slope2D.h"
#include <cmath>

namespace dims
{
	Slope2D::Slope2D()
	{
		Set(0, 0);
	}

	Slope2D::Slope2D(int Primary, int Secondary)
	{
		Set(Primary, Secondary);
	}

	void Slope2D::Set(int Primary, int Secondary, int Remainder /*= 0*/)
	{
		primary = Primary;
		secondary = Secondary;
		remainder = Remainder;
	}

	int Slope2D::IncrementPrimary(bool SlopeIsPositive)
	{
		//if 0 slope then we don't need to do anything - there should never be a 0-slope
		if (secondary == 0)
		{
			return 0;
		}
		//increment the remainder by the absolute value of the secondary slope value
		remainder += std::abs(secondary);

		//if the secondary slope value is positive then we only want to expand the view frustum if the remainder is greater or equal to the primary slope value
		//	else we will expand the view frustum once we have any non-negative remainder
		if (SlopeIsPositive)
		{
			if (remainder >= std::abs(primary))
			{
				//remainder should equal >= 0 after subtracting the primary slope value
				remainder -= std::abs(primary);
				if (secondary > 0)
				{
					return 1;
				}
				else if (secondary < 0)
				{
					return -1;
				}
			}
		}
		else
		{
			if (remainder >= 0)
			{
				//should bring the remainder to a negative value
				remainder -= std::abs(primary);
				if (secondary > 0)
				{
					return 1;
				}
				else if (secondary < 0)
				{
					return -1;
				}
			}
		}
		return 0;
	}

	Slope2D::~Slope2D()
	{

	}
}

