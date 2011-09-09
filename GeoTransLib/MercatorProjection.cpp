#include "StdAfx.h"
#include "MercatorProjection.h"
using namespace std;

double phi2z( double t, double e )
{
  auto ϕⁿ = M_PI_2 - 2*atan(t);
  auto ∆ϕ = 0.0;
  do
  {
    auto esinϕ = e*sin(ϕⁿ);
    auto ϕⁿ⁺¹ = M_PI_2 - 2*atan( t*pow( (1 - esinϕ)/(1 + esinϕ), e/2) );
    ∆ϕ = ϕⁿ⁺¹ - ϕⁿ;
    ϕⁿ = ϕⁿ⁺¹;
  } while ( ∆ϕ != 0 );

  return ϕⁿ;
}

MercatorProjection::MercatorProjection( double k₀, double λ₀, double FE, double FN, double a, double e )
{
  _ak₀ = a*k₀;
  _e   = e;
  _λ₀  = λ₀;
  _FE  = FE;
  _FN  = FN;
}

IProjection *MercatorProjection::Create1SP( double k₀, double λ₀, double FE, double FN, double a, double e )
{
  return new MercatorProjection( k₀, λ₀, FE, FN, a, e );
}

IProjection *MercatorProjection::Create2SP( double ϕ₁, double λ₀, double FE, double FN, double a, double e )
{
  auto e² = e*e;
  auto sinϕ₁ = sin(ϕ₁);
  auto sin²ϕ₁ = sinϕ₁*sinϕ₁;
  auto k₀ = cos(ϕ₁)/sqrt(1 - e²*sin²ϕ₁);

  return new MercatorProjection( k₀, λ₀, FE, FN, a, e );
}

void MercatorProjection::Project( double λ, double ϕ, double *E, double *N )
{
  auto esinϕ = _e*sin(ϕ);
  *E = _FE + _ak₀*(λ - _λ₀);
  *N = _FN + _ak₀*log( tan( M_PI_4 + ϕ/2 )*pow((1 - esinϕ)/(1 + esinϕ), _e/2) );
}

void MercatorProjection::Unproject( double E, double N, double *λ, double *ϕ )
{
  auto t = exp( (_FN-N)/_ak₀ );
  auto χ = M_PI_2 - 2*atan(t);
  *λ = (E - _FE)/_ak₀ + _λ₀;
  *ϕ = phi2z( t, _e );
}