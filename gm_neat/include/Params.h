#pragma once

#include "GarrysMod/Lua/Interface.h"

#include "Neat/Parameters.h"
#include "Neat/ActivationFunctions.h"


class BlackBoxParameters : public NEAT::Parameters
{
public:
	NEAT::ActivationFunction OutputActivationType;
	NEAT::ActivationFunction HiddenActivationType;
	int NumInputs;
	int NumHidden;
	int NumOutputs;
	int SeedType;
	int Seed;
	bool RandomizeWeights;
	double RandomWeightRange;
	double CompatThreshold;
	bool FSNeat;

public:
	BlackBoxParameters() : NEAT::Parameters()
	{
		Reset();
	}
	void Reset()
	{
		FSNeat = false;
		CompatThreshold = 0;
		OutputActivationType = NEAT::ActivationFunction::UNSIGNED_SIGMOID;
		HiddenActivationType = NEAT::ActivationFunction::UNSIGNED_SIGMOID;
		RandomizeWeights = false;
		FSNeat = false;
		Seed = 0;
		SeedType = 0;
		NumInputs = 0;
		NumOutputs = 0;
		NumHidden = 0;
		RandomWeightRange = 1.0;

		NEAT::Parameters::Reset();
	}
};

enum class ParameterFieldType
{
	DOUBLE,
	UINT,
	INT,
	BOOL,
};

struct ParameterField 
{
	const char *name;
	size_t offset;
	ParameterFieldType type;
};

static const ParameterField DefaultParams[] =
{
	{ "PopulationSize", offsetof(BlackBoxParameters, PopulationSize), ParameterFieldType::UINT },
	{ "DynamicCompatibility", offsetof(BlackBoxParameters, DynamicCompatibility), ParameterFieldType::BOOL },
	{ "MinSpecies", offsetof(BlackBoxParameters, MinSpecies), ParameterFieldType::UINT },
	{ "MaxSpecies", offsetof(BlackBoxParameters, MaxSpecies), ParameterFieldType::UINT },
	{ "InnovationsForever", offsetof(BlackBoxParameters, InnovationsForever), ParameterFieldType::BOOL },
	{ "AllowClones", offsetof(BlackBoxParameters, AllowClones), ParameterFieldType::BOOL },
	{ "CompatThreshold", offsetof(BlackBoxParameters, CompatThreshold), ParameterFieldType::BOOL },
	{ "YoungAgeTreshold", offsetof(BlackBoxParameters, YoungAgeTreshold), ParameterFieldType::UINT },
	{ "YoungAgeFitnessBoost", offsetof(BlackBoxParameters, YoungAgeFitnessBoost), ParameterFieldType::DOUBLE },
	{ "SpeciesMaxStagnation", offsetof(BlackBoxParameters, SpeciesMaxStagnation), ParameterFieldType::UINT },
	{ "StagnationDelta", offsetof(BlackBoxParameters, StagnationDelta), ParameterFieldType::DOUBLE },
	{ "OldAgeTreshold", offsetof(BlackBoxParameters, OldAgeTreshold), ParameterFieldType::UINT },
	{ "OldAgePenalty", offsetof(BlackBoxParameters, OldAgePenalty), ParameterFieldType::DOUBLE },
	{ "DetectCompetetiveCoevolutionStagnation", offsetof(BlackBoxParameters, DetectCompetetiveCoevolutionStagnation), ParameterFieldType::BOOL },
	{ "KillWorstSpeciesEach", offsetof(BlackBoxParameters, KillWorstSpeciesEach), ParameterFieldType::INT },
	{ "KillWorstAge", offsetof(BlackBoxParameters, KillWorstAge), ParameterFieldType::INT },
	{ "SurvivalRate", offsetof(BlackBoxParameters, SurvivalRate), ParameterFieldType::DOUBLE },
	{ "CrossoverRate", offsetof(BlackBoxParameters, CrossoverRate), ParameterFieldType::DOUBLE },
	{ "OverallMutationRate", offsetof(BlackBoxParameters, OverallMutationRate), ParameterFieldType::DOUBLE },
	{ "InterspeciesCrossoverRate", offsetof(BlackBoxParameters, InterspeciesCrossoverRate), ParameterFieldType::DOUBLE },
	{ "MultipointCrossoverRate", offsetof(BlackBoxParameters, MultipointCrossoverRate), ParameterFieldType::DOUBLE },
	{ "RouletteWheelSelection", offsetof(BlackBoxParameters, RouletteWheelSelection), ParameterFieldType::BOOL },
	{ "TournamentSize", offsetof(BlackBoxParameters, TournamentSize), ParameterFieldType::UINT },
	{ "EliteFraction", offsetof(BlackBoxParameters, EliteFraction), ParameterFieldType::DOUBLE },
	{ "PhasedSearching", offsetof(BlackBoxParameters, PhasedSearching), ParameterFieldType::BOOL },
	{ "DeltaCoding", offsetof(BlackBoxParameters, DeltaCoding), ParameterFieldType::BOOL },
	{ "SimplifyingPhaseMPCTreshold", offsetof(BlackBoxParameters, SimplifyingPhaseMPCTreshold), ParameterFieldType::UINT },
	{ "SimplifyingPhaseStagnationTreshold", offsetof(BlackBoxParameters, SimplifyingPhaseStagnationTreshold), ParameterFieldType::UINT },
	{ "ComplexityFloorGenerations", offsetof(BlackBoxParameters, ComplexityFloorGenerations), ParameterFieldType::UINT },
	{ "NoveltySearch_K", offsetof(BlackBoxParameters, NoveltySearch_K), ParameterFieldType::UINT },
	{ "NoveltySearch_P_min", offsetof(BlackBoxParameters, NoveltySearch_P_min), ParameterFieldType::DOUBLE },
	{ "NoveltySearch_Dynamic_Pmin", offsetof(BlackBoxParameters, NoveltySearch_Dynamic_Pmin), ParameterFieldType::DOUBLE },
	{ "NoveltySearch_No_Archiving_Stagnation_Treshold", offsetof(BlackBoxParameters, NoveltySearch_No_Archiving_Stagnation_Treshold), ParameterFieldType::UINT },
	{ "NoveltySearch_Pmin_lowering_multiplier", offsetof(BlackBoxParameters, NoveltySearch_Pmin_lowering_multiplier), ParameterFieldType::DOUBLE },
	{ "NoveltySearch_Pmin_min", offsetof(BlackBoxParameters, NoveltySearch_Pmin_min), ParameterFieldType::DOUBLE },
	{ "NoveltySearch_Quick_Archiving_Min_Evaluations", offsetof(BlackBoxParameters, NoveltySearch_Quick_Archiving_Min_Evaluations), ParameterFieldType::UINT },
	{ "NoveltySearch_Pmin_raising_multiplier", offsetof(BlackBoxParameters, NoveltySearch_Pmin_raising_multiplier), ParameterFieldType::DOUBLE },
	{ "NoveltySearch_Recompute_Sparseness_Each", offsetof(BlackBoxParameters, NoveltySearch_Recompute_Sparseness_Each), ParameterFieldType::UINT },
	{ "MutateAddNeuronProb", offsetof(BlackBoxParameters, MutateAddNeuronProb), ParameterFieldType::DOUBLE },
	{ "SplitRecurrent", offsetof(BlackBoxParameters, SplitRecurrent), ParameterFieldType::BOOL },
	{ "SplitLoopedRecurrent", offsetof(BlackBoxParameters, SplitLoopedRecurrent), ParameterFieldType::BOOL },
	{ "MutateAddLinkProb", offsetof(BlackBoxParameters, MutateAddLinkProb), ParameterFieldType::DOUBLE },
	{ "MutateAddLinkFromBiasProb", offsetof(BlackBoxParameters, MutateAddLinkFromBiasProb), ParameterFieldType::DOUBLE },
	{ "MutateRemLinkProb", offsetof(BlackBoxParameters, MutateRemLinkProb), ParameterFieldType::DOUBLE },
	{ "MutateRemSimpleNeuronProb", offsetof(BlackBoxParameters, MutateRemSimpleNeuronProb), ParameterFieldType::DOUBLE },
	{ "LinkTries", offsetof(BlackBoxParameters, LinkTries), ParameterFieldType::UINT },
	{ "RecurrentProb", offsetof(BlackBoxParameters, RecurrentProb), ParameterFieldType::DOUBLE },
	{ "RecurrentLoopProb", offsetof(BlackBoxParameters, RecurrentLoopProb), ParameterFieldType::DOUBLE },
	{ "MutateWeightsProb", offsetof(BlackBoxParameters, MutateWeightsProb), ParameterFieldType::DOUBLE },
	{ "MutateWeightsSevereProb", offsetof(BlackBoxParameters, MutateWeightsSevereProb), ParameterFieldType::DOUBLE },
	{ "WeightMutationRate", offsetof(BlackBoxParameters, WeightMutationRate), ParameterFieldType::DOUBLE },
	{ "WeightMutationMaxPower", offsetof(BlackBoxParameters, WeightMutationMaxPower), ParameterFieldType::DOUBLE },
	{ "WeightReplacementMaxPower", offsetof(BlackBoxParameters, WeightReplacementMaxPower), ParameterFieldType::DOUBLE },
	{ "MaxWeight", offsetof(BlackBoxParameters, MaxWeight), ParameterFieldType::DOUBLE },
	{ "MutateActivationAProb", offsetof(BlackBoxParameters, MutateActivationAProb), ParameterFieldType::DOUBLE },
	{ "MutateActivationBProb", offsetof(BlackBoxParameters, MutateActivationBProb), ParameterFieldType::DOUBLE },
	{ "ActivationAMutationMaxPower", offsetof(BlackBoxParameters, ActivationAMutationMaxPower), ParameterFieldType::DOUBLE },
	{ "ActivationBMutationMaxPower", offsetof(BlackBoxParameters, ActivationBMutationMaxPower), ParameterFieldType::DOUBLE },
	{ "MinActivationA", offsetof(BlackBoxParameters, MinActivationA), ParameterFieldType::DOUBLE },
	{ "MaxActivationA", offsetof(BlackBoxParameters, MaxActivationA), ParameterFieldType::DOUBLE },
	{ "MinActivationB", offsetof(BlackBoxParameters, MinActivationB), ParameterFieldType::DOUBLE },
	{ "MaxActivationB", offsetof(BlackBoxParameters, MaxActivationB), ParameterFieldType::DOUBLE },
	{ "TimeConstantMutationMaxPower", offsetof(BlackBoxParameters, TimeConstantMutationMaxPower), ParameterFieldType::DOUBLE },
	{ "BiasMutationMaxPower", offsetof(BlackBoxParameters, BiasMutationMaxPower), ParameterFieldType::DOUBLE },
	{ "MutateNeuronTimeConstantsProb", offsetof(BlackBoxParameters, MutateNeuronTimeConstantsProb), ParameterFieldType::DOUBLE },
	{ "MutateNeuronBiasesProb", offsetof(BlackBoxParameters, MutateNeuronBiasesProb), ParameterFieldType::DOUBLE },
	{ "MinNeuronTimeConstant", offsetof(BlackBoxParameters, MinNeuronTimeConstant), ParameterFieldType::DOUBLE },
	{ "MaxNeuronTimeConstant", offsetof(BlackBoxParameters, MaxNeuronTimeConstant), ParameterFieldType::DOUBLE },
	{ "MinNeuronBias", offsetof(BlackBoxParameters, MinNeuronBias), ParameterFieldType::DOUBLE },
	{ "MaxNeuronBias", offsetof(BlackBoxParameters, MaxNeuronBias), ParameterFieldType::DOUBLE },
	{ "MutateNeuronActivationTypeProb", offsetof(BlackBoxParameters, MutateNeuronActivationTypeProb), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_SignedSigmoid_Prob", offsetof(BlackBoxParameters, ActivationFunction_SignedSigmoid_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_UnsignedSigmoid_Prob", offsetof(BlackBoxParameters, ActivationFunction_UnsignedSigmoid_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_Tanh_Prob", offsetof(BlackBoxParameters, ActivationFunction_Tanh_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_TanhCubic_Prob", offsetof(BlackBoxParameters, ActivationFunction_TanhCubic_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_SignedStep_Prob", offsetof(BlackBoxParameters, ActivationFunction_SignedStep_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_UnsignedStep_Prob", offsetof(BlackBoxParameters, ActivationFunction_UnsignedStep_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_SignedGauss_Prob", offsetof(BlackBoxParameters, ActivationFunction_SignedGauss_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_UnsignedGauss_Prob", offsetof(BlackBoxParameters, ActivationFunction_UnsignedGauss_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_Abs_Prob", offsetof(BlackBoxParameters, ActivationFunction_Abs_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_SignedSine_Prob", offsetof(BlackBoxParameters, ActivationFunction_SignedSine_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_UnsignedSine_Prob", offsetof(BlackBoxParameters, ActivationFunction_UnsignedSine_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_Linear_Prob", offsetof(BlackBoxParameters, ActivationFunction_Linear_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_Relu_Prob", offsetof(BlackBoxParameters, ActivationFunction_Relu_Prob), ParameterFieldType::DOUBLE },
	{ "ActivationFunction_Softplus_Prob", offsetof(BlackBoxParameters, ActivationFunction_Softplus_Prob), ParameterFieldType::DOUBLE },
	{ "DisjointCoeff", offsetof(BlackBoxParameters, DisjointCoeff), ParameterFieldType::DOUBLE },
	{ "ExcessCoeff", offsetof(BlackBoxParameters, ExcessCoeff), ParameterFieldType::DOUBLE },
	{ "WeightDiffCoeff", offsetof(BlackBoxParameters, WeightDiffCoeff), ParameterFieldType::DOUBLE },
	{ "ActivationADiffCoeff", offsetof(BlackBoxParameters, ActivationADiffCoeff), ParameterFieldType::DOUBLE },
	{ "ActivationBDiffCoeff", offsetof(BlackBoxParameters, ActivationBDiffCoeff), ParameterFieldType::DOUBLE },
	{ "TimeConstantDiffCoeff", offsetof(BlackBoxParameters, TimeConstantDiffCoeff), ParameterFieldType::DOUBLE },
	{ "BiasDiffCoeff", offsetof(BlackBoxParameters, BiasDiffCoeff), ParameterFieldType::DOUBLE },
	{ "ActivationFunctionDiffCoeff", offsetof(BlackBoxParameters, ActivationFunctionDiffCoeff), ParameterFieldType::DOUBLE },
	{ "CompatTreshold", offsetof(BlackBoxParameters, CompatTreshold), ParameterFieldType::DOUBLE },
	{ "MinCompatTreshold", offsetof(BlackBoxParameters, MinCompatTreshold), ParameterFieldType::DOUBLE },
	{ "CompatTresholdModifier", offsetof(BlackBoxParameters, CompatTresholdModifier), ParameterFieldType::DOUBLE },
	{ "CompatTreshChangeInterval_Generations", offsetof(BlackBoxParameters, CompatTreshChangeInterval_Generations), ParameterFieldType::UINT },
	{ "CompatTreshChangeInterval_Evaluations", offsetof(BlackBoxParameters, CompatTreshChangeInterval_Evaluations), ParameterFieldType::UINT },
	{ "DivisionThreshold", offsetof(BlackBoxParameters, DivisionThreshold), ParameterFieldType::DOUBLE },
	{ "VarianceThreshold", offsetof(BlackBoxParameters, VarianceThreshold), ParameterFieldType::DOUBLE },
	{ "BandThreshold", offsetof(BlackBoxParameters, BandThreshold), ParameterFieldType::DOUBLE },
	{ "InitialDepth", offsetof(BlackBoxParameters, InitialDepth), ParameterFieldType::UINT },
	{ "MaxDepth", offsetof(BlackBoxParameters, MaxDepth), ParameterFieldType::UINT },
	{ "IterationLevel", offsetof(BlackBoxParameters, IterationLevel), ParameterFieldType::UINT },
	{ "CPPN_Bias", offsetof(BlackBoxParameters, CPPN_Bias), ParameterFieldType::DOUBLE },
	{ "Width", offsetof(BlackBoxParameters, Width), ParameterFieldType::DOUBLE },
	{ "Height", offsetof(BlackBoxParameters, Height), ParameterFieldType::DOUBLE },
	{ "Qtree_X", offsetof(BlackBoxParameters, Qtree_X), ParameterFieldType::DOUBLE },
	{ "Qtree_Y", offsetof(BlackBoxParameters, Qtree_Y), ParameterFieldType::DOUBLE },
	{ "Leo", offsetof(BlackBoxParameters, Leo), ParameterFieldType::BOOL },
	{ "LeoThreshold", offsetof(BlackBoxParameters, LeoThreshold), ParameterFieldType::DOUBLE },
	{ "LeoSeed", offsetof(BlackBoxParameters, LeoSeed), ParameterFieldType::BOOL },
	{ "GeometrySeed", offsetof(BlackBoxParameters, GeometrySeed), ParameterFieldType::BOOL },
	{ "OutputActivationType", offsetof(BlackBoxParameters, OutputActivationType), ParameterFieldType::UINT },
	{ "HiddenActivationType", offsetof(BlackBoxParameters, HiddenActivationType), ParameterFieldType::UINT },
	{ "RandomizeWeights", offsetof(BlackBoxParameters, RandomizeWeights), ParameterFieldType::BOOL },
	{ "Seed", offsetof(BlackBoxParameters, Seed), ParameterFieldType::UINT },
	{ "NumInputs", offsetof(BlackBoxParameters, NumInputs), ParameterFieldType::UINT },
	{ "NumHidden", offsetof(BlackBoxParameters, NumHidden), ParameterFieldType::UINT },
	{ "NumOutputs", offsetof(BlackBoxParameters, NumOutputs), ParameterFieldType::UINT },
	{ "RandomWeightRange", offsetof(BlackBoxParameters, RandomWeightRange), ParameterFieldType::DOUBLE },
};

inline void FillParameters(lua_State *state, int pos, BlackBoxParameters& params)
{
	for (size_t n = 0; n < sizeof(DefaultParams) / sizeof(DefaultParams[0]); n++)
	{
		const ParameterField& param = DefaultParams[n];

		LUA->PushString(param.name);
		LUA->GetTable(pos);
		if (LUA->IsType(-1, GarrysMod::Lua::Type::NIL) == false)
		{
			switch (param.type)
			{
			case ParameterFieldType::BOOL:
				{
					bool n = LUA->GetBool(-1);
					memcpy((char*)&params + param.offset, &n, sizeof(bool));
				}
				break;
			case ParameterFieldType::DOUBLE:
				{
					double n = LUA->GetNumber(-1);
					memcpy((char*)&params + param.offset, &n, sizeof(double));
				}
				break;
			case ParameterFieldType::UINT:
			case ParameterFieldType::INT:
				{
					unsigned int n = LUA->GetNumber(-1);
					memcpy((char*)&params + param.offset, &n, sizeof(unsigned int));
				}
				break;
			}
		}

		LUA->Pop();
	}
}