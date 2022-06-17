# win_api_test
A binary for testing detections for sensitive Windows API calls.

## Compilation

On Windows, with the appropriate developer tools installed, run `compile.bat`.

## Execution

The `apitest.exe` binary should be run with administrative privileges. When run, logs will be printed to the screen as well as saved to `log.txt`. Execution will take some time, as the program uses the `Sleep()` function to ensure temporal isolation of specific API calls in logs.
