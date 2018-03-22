#include "LuaIndividual.h"

Individual::Individual(NEAT::Genome& genome)
	: m_genome(genome)
{
}

void Individual::BuildPhenotype()
{
	m_genome.BuildPhenotype(m_network);
}

void Individual::Flush()
{
	m_network.Flush();
}

void Individual::FlushCube()
{
	m_network.FlushCube();
}

void Individual::SetFitness(double fitness)
{
	m_genome.SetFitness(fitness);
}

void Individual::SetEvaluated()
{
	m_genome.SetEvaluated();
}

unsigned int Individual::CountInputs()
{
	return m_genome.NumInputs();
}

unsigned int Individual::CountOutputs()
{
	return m_genome.NumOutputs();
}

void Individual::Inputs(std::vector<double>& inputs)
{
	m_network.Input(inputs);
}

void Individual::Activate()
{
	m_network.Activate();
}

void Individual::Outputs(std::vector<double>& outputs)
{
	outputs = m_network.Output();
}

namespace LuaIndividual {

int MetaTableRef = -1;

int GetMetatable(lua_State *state)
{
	if (MetaTableRef != -1)
		return MetaTableRef;

	LUA->CreateTable();
	{
		LUA->PushCFunction(Destroy);
		LUA->SetField(-2, "__gc");

		LUA->PushCFunction(ToString);
		LUA->SetField(-2, "__tostring");

		LUA->PushCFunction(ToString);
		LUA->SetField(-2, "__tostring");

		LUA->PushCFunction(Flush);
		LUA->SetField(-2, "Flush");

		LUA->PushCFunction(BuildPhenotype);
		LUA->SetField(-2, "BuildPhenotype");

		LUA->PushCFunction(Inputs);
		LUA->SetField(-2, "Inputs");

		LUA->PushCFunction(SetFitness);
		LUA->SetField(-2, "SetFitness");

		LUA->PushCFunction(Activate);
		LUA->SetField(-2, "Activate");

		LUA->PushCFunction(Outputs);
		LUA->SetField(-2, "Outputs");

		LUA->PushCFunction(SetEvaluated);
		LUA->SetField(-2, "SetEvaluated");

		LUA->Push(-1);
		LUA->SetField(-2, "__index");
	}

	MetaTableRef = LUA->ReferenceCreate();
	return MetaTableRef;
}

int Push(lua_State *state, void *ptr)
{
	int metaTable = GetMetatable(state);

	GarrysMod::Lua::UserData *ud = (GarrysMod::Lua::UserData*)LUA->NewUserdata(sizeof(GarrysMod::Lua::UserData));
	ud->data = ptr;
	ud->type = GarrysMod::Lua::Type::COUNT + 16; // ????

	LUA->ReferencePush(metaTable);
	LUA->SetMetaTable(-2);

	return 1;
}

Individual* ToIndividual(lua_State *state, int pos)
{
	GarrysMod::Lua::UserData *ud = (GarrysMod::Lua::UserData*)LUA->GetUserdata(pos);
	if (ud->type != GarrysMod::Lua::Type::COUNT + 16)
	{
		return nullptr;
	}
	return (Individual*)ud->data;
}


int Register(lua_State *state)
{
	return 0;
}

int ToString(lua_State *state)
{
	return 0;
}


int Destroy(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}

	delete individual;
	return 0;
}


int Flush(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}
	individual->Flush();

	return 0;
}

int Inputs(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}
	
	LUA->CheckType(2, GarrysMod::Lua::Type::TABLE);

	unsigned int numInputs = individual->CountInputs();

	std::vector<double> inputs;
	inputs.resize(numInputs);

	for (unsigned int i = 0; i < numInputs; i++)
	{
		LUA->PushNumber(i + 1);
		LUA->GetTable(2);
		inputs[i] = LUA->CheckNumber(-1);
		LUA->Pop();
	}

	individual->Inputs(inputs);

	return 0;
}

int BuildPhenotype(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}
	
	individual->BuildPhenotype();

	return 0;
}

int SetFitness(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}

	double fitness = LUA->CheckNumber(2);

	individual->SetFitness(fitness);

	return 0;
}

int SetEvaluated(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}

	individual->SetEvaluated();

	return 0;
}

int Activate(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}

	individual->Activate();

	return 0;
}

int Outputs(lua_State *state)
{
	Individual *individual = ToIndividual(state, 1);
	if (!individual)
	{
		LUA->ArgError(1, "Parameter not Individual");
		return 0;
	}

	std::vector<double> outputs;
	individual->Outputs(outputs);

	LUA->CreateTable();
	{
		for (unsigned int i = 0; i < outputs.size(); i++)
		{
			LUA->PushNumber(i + 1);
			LUA->PushNumber(outputs[i]);
			LUA->SetTable(-3);
		}
	}

	return 1;
}

}
