#pragma once

#include "IProjection.h"

class MercatorProjection : public IProjection
{
private:
  double _ak₀;
  double _e;
  double _λ₀;
  double _FE;
  double _FN;

public:

  MercatorProjection( double k₀, double λ₀, double FE, double FN, double a, double e );

  /// <param name="k₀">The scale factor at the Equator</param>
  /// <param name="λ₀">The longitude of the natural origin</param>
  /// <param name="FE">The value assigned to the abscissa (east or west) axis of the projection grid at the natural origin.</param>
  /// <param name="FN">The value assigned to the ordinate (north or south) axis of the projection grid at the natural origin.</param>
  /// <param name="a">Length of the semi-major axis of the ellipsoid, the radius of the equator.</param>
  /// <param name="e">The eccentricity of the ellipsoid.</param>
  static IProjection *Create1SP( double k₀, double λ₀, double FE, double FN, double a, double e );

  /// <param name="ϕ₁">The latitude of one of the two parallels equidistant either side of the equator upon which the grid scale is true</param>
  /// <param name="λ₀">The longitude of the natural origin</param>
  /// <param name="FE">The value assigned to the abscissa (east or west) axis of the projection grid at the natural origin.</param>
  /// <param name="FN">The value assigned to the ordinate (north or south) axis of the projection grid at the natural origin.</param>
  /// <param name="a">Length of the semi-major axis of the ellipsoid, the radius of the equator.</param>
  /// <param name="e">The eccentricity of the ellipsoid.</param>
  static IProjection *Create2SP( double ϕ₁, double λ₀, double FE, double FN, double a, double e );

  virtual void Project( double λ, double ϕ, double *E, double *N ) override;
  virtual void Unproject( double E, double N, double *λ, double *ϕ ) override;
};

