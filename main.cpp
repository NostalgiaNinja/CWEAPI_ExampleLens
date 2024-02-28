#include "pch.h"
#include "cwe_api.h"
#include "ModelInfo.h"

extern "C"
{
	//registering data functions.
	void (*RegisterDataFunc)(void* ptr);

	//Lens function - Needed for CWE to recognize the lens.
	__declspec(dllexport) void(__cdecl* ALS_LensSpecial)(ObjectMaster*, ObjectMaster*);

	//NJS Type texture name and texture list. As is for old documentation.
	NJS_TEXNAME ExampleLensTex[10];
	NJS_TEXLIST Example_texlist = { arrayptrandlength(ExampleLensTex) };

	//define models
	ModelInfo* MDLExampleLensBox;

	//Generate an ID for each lens
	int ExampleLensID;

	//Black Market registration code
	BlackMarketItemAttributes BMExampleLens = { 300, 150, 0, -1, -1, 0 };;

	//main CWE Load function -- Important stuff like adding your CWE mod goes here
	void CWELoad(CWE_REGAPI* cwe_api)
	{
		//Register your textures here (by filename.pak)
		cwe_api->RegisterChaoTexlistLoad("ExampleLens", &Example_texlist);
		
		//Register your lens to the black market:
		cwe_api->RegisterChaoSpecial(MDLExampleLensBox->getmodel(), &Example_texlist, &BMExampleLens, ALS_LensSpecial, NULL, "Lens Name", "Lens Description", 0);

		//Associate the lens as a custom eye color:
		cwe_api->RegisterEyeColor("testlens", &Example_texlist, ExampleLensID);

	}

	__declspec(dllexport) void Init(const char* path)
	{
		HMODULE h = GetModuleHandle(L"CWE");

		std::string pathStr = std::string(path) + "\\";

		//Lens function declarative - This talks to CWE to get the lens to work when registering it as a special object.
		ALS_LensSpecial = (decltype(ALS_LensSpecial))GetProcAddress(GetModuleHandle(L"CWE"), "ALS_LensSpecial");

		//Tell what models need to be associated to their variables here.
		MDLExampleLensBox = new ModelInfo(pathStr = "lens.sa2mdl");

		RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
		RegisterDataFunc(CWELoad);
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}