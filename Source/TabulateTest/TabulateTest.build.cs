using UnrealBuildTool;
 
public class TabulateTest : ModuleRules
{
	public TabulateTest(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
	        new string[]
	        {
		        "Core", 
		        "CoreUObject",
		        "Engine",
		        "Tabulate", 
		        "Slate", 
		        "SlateCore"
	        });
	}
}