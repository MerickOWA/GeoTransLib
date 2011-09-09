#define _USE_MATH_DEFINES

#include <cmath>

#include "Assert.h"
#include "../GeoTransLib/MercatorProjection.h"

#define WIN_ASSERT_ARE_EQUIVALENT( expected, actual, tolerance, ... )

#define DEG2RAD (M_PI/180)
#define RAD2DEG (180/M_PI)

BEGIN_TEST(MercatorTest1)
{
  double k₀ = 0.997;
  double λ₀ = 110*DEG2RAD;
  double FE = 3900000.00;
  double FN =  900000.00;
  double a  = 6377397.155;
  double f  = 1/299.15281;
  double e  = sqrt( 2*f - f*f );
  auto proj = MercatorProjection::Create1SP( k₀, λ₀, FE, FN, a, e );

  double λₑ = 120*DEG2RAD;
  double ϕₑ = -3*DEG2RAD;
  double Eₑ =5009726.58;
  double Nₑ = 569150.82;

  double Eₐ,Nₐ;
  proj->Project( λₑ, ϕₑ, &Eₐ, &Nₐ );

  WIN_ASSERT_EQUAL_TOL( Eₑ, Eₐ, 0.005 );
  WIN_ASSERT_EQUAL_TOL( Nₑ, Nₐ, 0.005 );

  double λₐ, ϕₐ;
  proj->Unproject( Eₐ, Nₐ, &λₐ, &ϕₐ );

  WIN_ASSERT_EQUAL_TOL( λₑ, λₐ, 2.4241e-9 );
  WIN_ASSERT_EQUAL_TOL( ϕₑ, ϕₐ, 2.4241e-9 );
}
END_TEST

BEGIN_TEST(MercatorTest2)
{
  double ϕ₁ = 42*DEG2RAD;
  double λ₀ = 51*DEG2RAD;
  double FE = 0.00;
  double FN = 0.00;
  double a  = 6378245.0;
  double f  = 1/298.3;
  double e  = sqrt( 2*f - f*f );
  auto proj = MercatorProjection::Create2SP( ϕ₁, λ₀, FE, FN, a, e );

  double λₑ = 53*DEG2RAD;
  double ϕₑ = 53*DEG2RAD;
  double Eₑ =  165704.29;
  double Nₑ = 5171848.07;

  double Eₐ,Nₐ;
  proj->Project( λₑ, ϕₑ, &Eₐ, &Nₐ );

  WIN_ASSERT_EQUAL_TOL( Eₑ, Eₐ, 0.005 );
  WIN_ASSERT_EQUAL_TOL( Nₑ, Nₐ, 0.005 );

  double λₐ, ϕₐ;
  proj->Unproject( Eₐ, Nₐ, &λₐ, &ϕₐ );

  WIN_ASSERT_EQUAL_TOL( λₑ, λₐ, 2.4241e-9 );
  WIN_ASSERT_EQUAL_TOL( ϕₑ, ϕₐ, 2.4241e-9 );
}
END_TEST