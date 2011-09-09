#pragma once

class IProjection
{
public:
  virtual ~IProjection() {}

  virtual void Project( double λ, double ϕ, double *E, double *N ) = 0;
  virtual void Unproject( double E, double N, double *λ, double *ϕ ) = 0;
};

