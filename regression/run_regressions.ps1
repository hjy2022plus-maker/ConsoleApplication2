param(
    [string]$Binary = "..\\build-verify\\regression-check.exe"
)

$ErrorActionPreference = "Stop"

$cases = @(
    @{
        Name = "stage31_headlights_then_car"
        Path = "stage31_headlights_then_car.txt"
        Checks = @("0_0", "Game Statistics", "(x>")
    },
    @{
        Name = "stage31_headlights_then_leave"
        Path = "stage31_headlights_then_leave.txt"
        Checks = @("0_0", "^_^")
        Rejects = @("(x>")
    },
    @{
        Name = "stage34_tunnel_scroll_basic"
        Path = "stage34_tunnel_scroll_basic.txt"
        Checks = @("(0)", "Quitting Game")
    },
    @{
        Name = "stage34_tunnel_scroll_with_blocker"
        Path = "stage34_tunnel_scroll_with_blocker.txt"
        Checks = @("(0)", " T ", "Quitting Game")
    },
    @{
        Name = "stage34_tunnel_scroll_to_top"
        Path = "stage34_tunnel_scroll_to_top.txt"
        Checks = @("(0)", "Quitting Game")
    }
)

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$binaryPath = Join-Path $scriptDir $Binary

foreach ($case in $cases) {
    $inputPath = Join-Path $scriptDir $case.Path
    $text = ((Get-Content $inputPath | & $binaryPath) -join "`n")

    foreach ($needle in $case.Checks) {
        if ($text -notmatch [regex]::Escape($needle)) {
            throw "Case '$($case.Name)' missing expected text: $needle"
        }
    }

    foreach ($needle in $case.Rejects) {
        if ($text -match [regex]::Escape($needle)) {
            throw "Case '$($case.Name)' contained unexpected text: $needle"
        }
    }

    Write-Host "[PASS] $($case.Name)"
}
