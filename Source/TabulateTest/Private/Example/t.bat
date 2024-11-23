@echo off
setlocal

REM 遍历当前目录下的所有 .cpp 文件
for %%f in (*.cpp) do (
    PowerShell -Command "(Get-Content -Path '%%f') -replace 'MEIJIWEI', 'IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTabulate%%~nf, \"Tabulate.%%~nf\", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)' | Set-Content -Path '%%f'"

    PowerShell -Command "(Get-Content -Path '%%f') -replace 'int main', 'bool FTabulate%%~nf::RunTest(const FString& Parameters)' | Set-Content -Path '%%f'"

)

echo 替换完成！
pause