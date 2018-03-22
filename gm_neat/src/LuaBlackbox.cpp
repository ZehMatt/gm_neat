#include "LuaBlackbox.h"
#include "LuaIndividual.h"
#include "Params.h"

Blackbox::Blackbox(int numInputs,
				   int numHidden,
				   int numOutputs,
				   bool FSNeat,
				   NEAT::ActivationFunction hiddenActFunc,
				   NEAT::ActivationFunction outputActFunc,
				   int seedType,
				   bool randomizeWeights,
				   double weightRange,
				   int seed,
				   const NEAT::Parameters& params) :
	m_genome(0, numInputs, numHidden, numOutputs, FSNeat, hiddenActFunc, outputActFunc, seedType, params),
	m_population(m_genome, params, randomizeWeights, weightRange, seed)
{
}

int Blackbox::CountSpecies() const
{
	return m_population.m_Species.size();
}

int Blackbox::CountIndividuals(int speciesIndex)
{
	if (speciesIndex >= m_population.m_Species.size())
		return -1;

	return m_population.m_Species[speciesIndex].NumIndividuals();
}

NEAT::Genome* Blackbox::GetIndividual(int speciesIdx, int individualIdx)
{
	if (speciesIdx >= m_population.m_Species.size())
		return nullptr;

	NEAT::Species& species = m_population.m_Species[speciesIdx];
	if (individualIdx > species.m_Individuals.size())
		return nullptr;

	return &species.m_Individuals[individualIdx];
}

NEAT::Genome* Blackbox::GetBestIndividual()
{
	m_bestGenome = m_population.GetBestGenome();
	return &m_bestGenome;
}

void Blackbox::NextEpoch()
{
	return m_population.Epoch();
}

double Blackbox::GetCurrentMPC() const
{
	return m_population.GetCurrentMPC();
}

double Blackbox::GetBaseMPC() const
{
	return m_population.GetBaseMPC();
}

namespace LuaBlackbox {

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

		LUA->PushCFunction(CountSpecies);
		LUA->SetField(-2, "CountSpecies");

		LUA->PushCFunction(CountIndividuals);
		LUA->SetField(-2, "CountIndividuals");

		LUA->PushCFunction(GetIndividual);
		LUA->SetField(-2, "GetIndividual");

		LUA->PushCFunction(GetBestIndividual);
		LUA->SetField(-2, "GetBestIndividual");

		LUA->PushCFunction(GetCurrentMPC);
		LUA->SetField(-2, "GetCurrentMPC");

		LUA->PushCFunction(GetCurrentMPC);
		LUA->SetField(-2, "GetBaseMPC");

		LUA->PushCFunction(NextEpoch);
		LUA->SetField(-2, "NextEpoch");

		LUA->Push(-1);
		LUA->SetField(-2, "__index");
	}

	MetaTableRef = LUA->ReferenceCreate();
	return MetaTableRef;
}

int PushBlackbox(lua_State *state, void *ptr)
{
	int metaTable = GetMetatable(state);

	GarrysMod::Lua::UserData *ud = (GarrysMod::Lua::UserData*)LUA->NewUserdata(sizeof(GarrysMod::Lua::UserData));
	ud->data = ptr;
	ud->type = GarrysMod::Lua::Type::COUNT + 15; // ????

	LUA->ReferencePush(metaTable);
	LUA->SetMetaTable(-2);

	return 1;
}

Blackbox* ToBlackBox(lua_State *state, int pos)
{
	GarrysMod::Lua::UserData *ud = (GarrysMod::Lua::UserData*)LUA->GetUserdata(pos);
	if (ud->type != GarrysMod::Lua::Type::COUNT + 15)
	{
		return nullptr;
	}
	return (Blackbox*)ud->data;
}

int Register(lua_State *state)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushString("BlackBox");
	LUA->CreateTable();
	{
		LUA->PushCFunction(Create);
		LUA->SetField(-2, "Create");
	}
	LUA->SetTable(-3);

	return 0;
}

int Create(lua_State *state)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::TABLE);

	BlackBoxParameters params;
	FillParameters(state, 1, params);

	Blackbox *blackBox = new Blackbox(params.NumInputs,
									  params.NumHidden,
									  params.NumOutputs,
									  params.FSNeat,
									  params.HiddenActivationType,
									  params.OutputActivationType,
									  params.SeedType,
									  params.RandomizeWeights,
									  params.RandomWeightRange,
									  params.Seed,
									  params);

	PushBlackbox(state, blackBox);

	return 1;
}

int ToString(lua_State *state)
{
	return 0;
}

int Destroy(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	delete blackBox;
	return 0;
}

int CountSpecies(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	LUA->PushNumber(blackBox->CountSpecies());
	return 1;
}

int CountIndividuals(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}
	int speciesIdx = LUA->CheckNumber(2);

	LUA->PushNumber(blackBox->CountIndividuals(speciesIdx));
	return 1;
}

int GetIndividual(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	int speciesIdx = LUA->CheckNumber(2);
	int individualIdx = LUA->CheckNumber(3);

	NEAT::Genome *genome = blackBox->GetIndividual(speciesIdx, individualIdx);
	if (!genome)
	{
		LUA->PushNil();
	}
	else
	{
		Individual *individual = new Individual(*genome);
		LuaIndividual::Push(state, individual);
	}
	
	return 1;
}

int GetBestIndividual(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	NEAT::Genome *genome = blackBox->GetBestIndividual();
	if (!genome)
	{
		LUA->PushNil();
	}
	else
	{
		Individual *individual = new Individual(*genome);
		LuaIndividual::Push(state, individual);
	}

	return 1;
}

int NextEpoch(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	blackBox->NextEpoch();

	return 0;
}

int GetCurrentMPC(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	LUA->PushNumber(blackBox->GetCurrentMPC());

	return 1;
}


int GetBaseMPC(lua_State *state)
{
	Blackbox *blackBox = ToBlackBox(state, 1);
	if (!blackBox)
	{
		LUA->ArgError(1, "Parameter not BlackBox");
		return 0;
	}

	LUA->PushNumber(blackBox->GetBaseMPC());

	return 1;
}

}
