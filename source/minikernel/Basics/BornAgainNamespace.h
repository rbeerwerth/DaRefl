// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/BornAgainNamespace.h
//! @brief     Defines BornAgain namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_BORNAGAINNAMESPACE_H
#define BORNAGAIN_CORE_BASICS_BORNAGAINNAMESPACE_H

#include <string>

//! Mostly names of classes and parameters.

namespace BornAgain
{
// Axis constants
const std::string PHI_AXIS_NAME = "phi_f";
const std::string ALPHA_AXIS_NAME = "alpha_f";
const std::string U_AXIS_NAME = "u";
const std::string V_AXIS_NAME = "v";
const size_t X_AXIS_INDEX = 0;
const size_t Y_AXIS_INDEX = 1;

// Simulation types
const std::string GISASSimulationType = "GISASSimulation";
const std::string OffSpecSimulationType = "OffSpecSimulation";
const std::string SpecularSimulationType = "SpecularSimulation";
const std::string DepthProbeSimulationType = "DepthProbeSimulation";

// Instrument related constants
const std::string InstrumentType = "Instrument";
const std::string ResolutionFunction2D = "ResolutionFunction2D";
const std::string DetectorType = "Detector";
const std::string SphericalDetectorType = "SphericalDetector";
const std::string RectangularDetectorType = "RectangularDetector";
const std::string IsGISAXSDetectorType = "IsGISAXSDetector";
const std::string SpecularDetectorType = "SpecularDetector1D";
const std::string BeamType = "Beam";
const std::string GaussianFootprintFactorType = "FootprintFactorGaussian";
const std::string SquareFootprintFactorType = "FootprintFactorSquare";
const std::string DetectorAnalyzer = "Analyzer";
const std::string ConstantBackgroundType = "ConstantBackground";
const std::string PoissonNoiseBackgroundType = "PoissonNoiseBackground";

// ISample object types
const std::string MultiLayerType = "MultiLayer";
const std::string LayerType = "Layer";
const std::string LayerInterfaceType = "LayerInterface";
const std::string ParticleLayoutType = "ParticleLayout";
const std::string ParticleType = "Particle";
const std::string ParticleCoreShellType = "ParticleCoreShell";
const std::string ParticleDistributionType = "ParticleDistribution";
const std::string ParticleCompositionType = "ParticleComposition";
const std::string TransformationType = "Rotation";

const std::string LayerBasicRoughnessType = "LayerBasicRoughness";
const std::string LayerZeroRoughnessType = "LayerZeroRoughness";

const std::string BasicLatticeType = "BasicLattice";
const std::string SquareLatticeType = "SquareLattice";
const std::string HexagonalLatticeType = "HexagonalLattice";

const std::string InterferenceFunctionNoneType = "InterferenceNone";
const std::string InterferenceFunction1DLatticeType = "Interference1DLattice";
const std::string InterferenceFunction2DLatticeType = "Interference2DLattice";
const std::string InterferenceFunction2DParaCrystalType = "Interference2DParaCrystal";
const std::string InterferenceFunction2DSuperLattice = "Interference2DSuperLattice";
const std::string InterferenceFunction3DLatticeType = "Interference3DLattice";
const std::string InterferenceFunctionFinite2DLatticeType = "InterferenceFinite2DLattice";
const std::string InterferenceFunctionFinite3DLatticeType = "InterferenceFinite3DLattice";
const std::string InterferenceFunctionHardDiskType = "InterferenceHardDisk";
const std::string InterferenceFunctionRadialParaCrystalType = "InterferenceRadialParaCrystal";
const std::string InterferenceFunctionTwinType = "InterferenceTwin";

const std::string CrystalType = "Crystal";
const std::string LatticeType = "Lattice";
const std::string MesoCrystalType = "MesoCrystal";

const std::string FF2DLattice = "2DLatticeFF";
const std::string FFAnisoPyramidType = "AnisoPyramid";
const std::string FFBoxType = "Box";
const std::string FFConeType = "Cone";
const std::string FFCone6Type = "Cone6";
const std::string FFCuboctahedronType = "Cuboctahedron";
const std::string FFCylinderType = "Cylinder";
const std::string FFDebyeBuecheType = "FormFactorDebyeBueche";
const std::string FFDodecahedronType = "Dodecahedron";
const std::string FFDotType = "Dot";
const std::string FFEllipsoidalCylinderType = "EllipsoidalCylinder";
const std::string FFFullSphereType = "FullSphere";
const std::string FFFullSpheroidType = "FullSpheroid";
const std::string FFGaussType = "FormFactorGauss";
const std::string FFHemiEllipsoidType = "HemiEllipsoid";
const std::string FFIcosahedronType = "Icosahedron";
const std::string FFLongBoxGaussType = "FormFactorLongBoxGauss";
const std::string FFLongBoxLorentzType = "FormFactorLongBoxLorentz";
const std::string FFLorentzType = "FormFactorLorentz";
const std::string FFOrnsteinZernikeType = "FormFactorOrnsteinZernike";
const std::string FFPrism3Type = "Prism3";
const std::string FFPrism6Type = "Prism6";
const std::string FFPyramidType = "Pyramid";
const std::string FFBarGaussType = "BarGauss";
const std::string FFBarLorentzType = "BarLorentz";
const std::string FFRipple1BoxType = "Ripple1Box";
const std::string FFRipple1GaussType = "Ripple1Gauss";
const std::string FFRipple1LorentzType = "Ripple1Lorentz";
const std::string FFRipple2BoxType = "Ripple2Box";
const std::string FFRipple2GaussType = "Ripple2Gauss";
const std::string FFRipple2LorentzType = "Ripple2Lorentz";
const std::string FFTetrahedronType = "Tetrahedron";
const std::string FFTruncatedCubeType = "TruncatedCube";
const std::string FFTruncatedSphereType = "TruncatedSphere";
const std::string FFTruncatedSpheroidType = "TruncatedSpheroid";

const std::string FormFactorCrystalType = "FormFactorCrystal";
const std::string FormFactorSphereGaussianRadiusType = "FormFactorSphereGaussianRadius";
const std::string FormFactorSphereLogNormalRadiusType = "FormFactorSphereLogNormalRadius";
const std::string FormFactorSphereUniformRadiusType = "FormFactorSphereUniformRadius";
const std::string FormFactorDWBAType = "FormFactorDWBA";
const std::string FormFactorPolarizedDWBAType = "FormFactorDWBAPol";
const std::string FormFactorPolarizedBAType = "FormFactorBAPol";

const std::string FormFactorCoreShellType = "FormFactorCoreShell";
const std::string FormFactorDecoratorPositionFactorType = "FormFactorDecoratorPositionFactor";
const std::string FormFactorDecoratorRotationType = "FormFactorDecoratorRotation";
const std::string FormFactorDecoratorMaterialType = "FormFactorDecoratorMaterial";
const std::string FormFactorWeightedType = "FormFactorWeighted";

const std::string XRotationType = "XRotation";
const std::string YRotationType = "YRotation";
const std::string ZRotationType = "ZRotation";
const std::string EulerRotationType = "EulerRotation";

const std::string DistributionNoneType = "DistributionNone";
const std::string DistributionGateType = "DistributionGate";
const std::string DistributionLorentzType = "DistributionLorentz";
const std::string DistributionGaussianType = "DistributionGaussian";
const std::string DistributionLogNormalType = "DistributionLogNormal";
const std::string DistributionCosineType = "DistributionCosine";
const std::string DistributionTrapezoidType = "DistributionTrapezoid";

const std::string FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const std::string FTDistribution1DGaussType = "FTDistribution1DGauss";
const std::string FTDistribution1DGateType = "FTDistribution1DGate";
const std::string FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const std::string FTDistribution1DCosineType = "FTDistribution1DCosine";
const std::string FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const std::string FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const std::string FTDistribution2DGaussType = "FTDistribution2DGauss";
const std::string FTDistribution2DGateType = "FTDistribution2DGate";
const std::string FTDistribution2DConeType = "FTDistribution2DCone";
const std::string FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const std::string FTDecayFunction1DCauchyType = "FTDecayFunction1DCauchy";
const std::string FTDecayFunction1DGaussType = "FTDecayFunction1DGauss";
const std::string FTDecayFunction1DTriangleType = "FTDecayFunction1DTriangle";
const std::string FTDecayFunction1DVoigtType = "FTDecayFunction1DVoigt";

const std::string FTDecayFunction2DCauchyType = "FTDecayFunction2DCauchy";
const std::string FTDecayFunction2DGaussType = "FTDecayFunction2DGauss";
const std::string FTDecayFunction2DVoigtType = "FTDecayFunction2DVoigt";

const std::string SampleBuilderType = "SampleBuilder";

// Parameter names (dimensions, angles, ...)
const std::string Abundance = "Abundance";
const std::string Position = "Position";
const std::string BasisVector_A = "BasisA";
const std::string BasisVector_B = "BasisB";
const std::string BasisVector_C = "BasisC";
const std::string Radius = "Radius";
const std::string RadiusX = "RadiusX";
const std::string RadiusY = "RadiusY";
const std::string MeanRadius = "MeanRadius";
const std::string SigmaRadius = "SigmaRadius";
const std::string FullWidth = "FullWidth";
const std::string Edge = "Edge";
const std::string BaseEdge = "BaseEdge";
const std::string Length = "Length";
const std::string PositionVariance = "PositionVariance";
const std::string RemovedLength = "RemovedLength";
const std::string Width = "Width";
const std::string LeftWidth = "LeftWidth";
const std::string MiddleWidth = "MiddleWidth";
const std::string RightWidth = "RightWidth";
const std::string Center = "Center";
const std::string Height = "Height";
const std::string HeightRatio = "HeightRatio";
const std::string HeightFlattening = "HeightFlattening";
const std::string DeltaHeight = "DeltaHeight";
const std::string Weight = "Weight";
const std::string Intensity = "Intensity";
const std::string Wavelength = "Wavelength";
const std::string Angle = "Angle";
const std::string Alpha = "Alpha";
const std::string Beta = "Beta";
const std::string Gamma = "Gamma";
const std::string Delta = "Delta";
const std::string Phi = "Phi";
const std::string Xi = "Xi";
const std::string Minimum = "Min";
const std::string Maximum = "Max";
const std::string Mean = "Mean";
const std::string StdDeviation = "StdDev";
const std::string HWHM = "HWHM";
const std::string Median = "Median";
const std::string ScaleParameter = "ScaleParameter";
const std::string Sigma = "Sigma";
const std::string Eta = "Eta";
const std::string Omega = "Omega";
const std::string OmegaX = "OmegaX";
const std::string OmegaY = "OmegaY";
const std::string DecayLength = "DecayLength";
const std::string DecayLengthX = "DecayLengthX";
const std::string DecayLengthY = "DecayLengthY";
const std::string SigmaX = "SigmaX";
const std::string SigmaY = "SigmaY";
const std::string HeightDWFactor = "HeightDWFactor";
const std::string RadiusDWFactor = "RadiusDWFactor";
const std::string AsymmetryLength = "AsymmetryLength";
const std::string LatticeLength = "LatticeLength";
const std::string LatticeLength1 = "LatticeLength1";
const std::string LatticeLength2 = "LatticeLength2";
const std::string LatticeAngle = "Alpha";
const std::string DampingLength = "DampingLength";
const std::string DomainSize = "DomainSize";
const std::string DomainSize1 = "DomainSize1";
const std::string DomainSize2 = "DomainSize2";
const std::string PeakDistance = "PeakDistance";
const std::string SizeSpaceCoupling = "SizeSpaceCoupling";
const std::string Thickness = "Thickness";
const std::string Hurst = "Hurst";
const std::string CorrelationLength = "CorrelationLength";
const std::string CrossCorrelationLength = "CrossCorrelationLength";
const std::string Inclination = "InclinationAngle";
const std::string Azimuth = "AzimuthalAngle";
const std::string TotalParticleDensity = "TotalParticleDensity";
const std::string ExternalField = "ExternalField";
const std::string BlochVector = "BlochVector";
const std::string Direction = "Direction";
const std::string Efficiency = "Efficiency";
const std::string Transmission = "Transmission";
const std::string BackgroundValue = "BackgroundValue";
const std::string BeamToSampleWidthRatio = "BeamToSampleWidthRatio";

const std::string UnitsRad = "rad";
const std::string UnitsNm = "nm";
const std::string UnitsNm2 = "nm^2";
const std::string UnitsNone = "";
} // namespace BornAgain

#endif // BORNAGAIN_CORE_BASICS_BORNAGAINNAMESPACE_H
