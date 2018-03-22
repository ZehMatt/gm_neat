#pragma once 

#include "GarrysMod/Lua/Interface.h"

#include "Neat/Genome.h"
#include "Neat/NeuralNetwork.h"
#include "Neat/Population.h"

class Individual
{
private:
	NEAT::Genome& m_genome;
	NEAT::NeuralNetwork m_network;

public:
	Individual(NEAT::Genome& genome);

	void BuildPhenotype();
	void Flush();
	void FlushCube();
	void SetFitness(double fitness);
	void SetEvaluated();
	unsigned int CountInputs();
	unsigned int CountOutputs();
	void Inputs(std::vector<double>& inputs);
	void Activate();
	void Outputs(std::vector<double>& outputs);
};

namespace LuaIndividual {

int Push(lua_State *state, void *ptr);

int Register(lua_State *state);

int ToString(lua_State *state);
int Destroy(lua_State *state);

int Flush(lua_State *state);
int BuildPhenotype(lua_State *state);
int Inputs(lua_State *state);
int SetFitness(lua_State *state);
int SetEvaluated(lua_State *state);
int Activate(lua_State *state);
int Outputs(lua_State *state);

}

