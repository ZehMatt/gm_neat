#pragma once 

#include "GarrysMod/Lua/Interface.h"

#include "Neat/Genome.h"
#include "Neat/NeuralNetwork.h"
#include "Neat/Population.h"

class Blackbox
{
private:
	NEAT::Genome m_genome;
	NEAT::Genome m_bestGenome;
	NEAT::Population m_population;

public:
	Blackbox(int numInputs,
			 int numHidden,
			 int numOutputs,
			 bool FSNeat,
			 NEAT::ActivationFunction hiddenActFunc,
			 NEAT::ActivationFunction outputActFunc,
			 int seedType,
			 bool randomizeWeights,
			 double weightRange,
			 int seed,
			 const NEAT::Parameters& params);

	int CountSpecies() const;
	int CountIndividuals(int speciesIndex);
	NEAT::Genome* GetIndividual(int speciesIdx, int individualIdx);
	NEAT::Genome* GetBestIndividual();
	void NextEpoch();
	double GetCurrentMPC() const;
	double GetBaseMPC() const;
};


namespace LuaBlackbox
{

int Register(lua_State *state);

int Create(lua_State *state);
int ToString(lua_State *state);
int Destroy(lua_State *state);

int CountSpecies(lua_State *state);
int CountIndividuals(lua_State *state);
int GetIndividual(lua_State *state);
int GetBestIndividual(lua_State *state);

int NextEpoch(lua_State *state);
int GetCurrentMPC(lua_State *state);
int GetBaseMPC(lua_State *state);

}