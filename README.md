**English** | [العربية](README.ar.md)

# C++ Utility Library

An educational collection of reusable C++ helper functions. The project groups random-data generation, array operations, swapping, simple text transformation, and date utilities into class-based headers.

## Utility Features

- Seed and generate pseudo-random numbers
- Generate lowercase letters, uppercase letters, digits, mixed characters, words, and formatted keys
- Swap integers, doubles, strings, and `clsDate` objects
- Print, shuffle, and fill fixed-size arrays
- Create tab indentation strings
- Apply a basic character-shift transformation and reverse it
- Reuse the bundled `clsDate` helper for date calculations

## Tech Stack

- C++
- Static class methods and function overloading
- Microsoft Visual C++ / Visual Studio
- Standard Library strings, vectors, streams, and time functions

## Project Structure

```text
Utility_Library/
├── Utility Library.vcxproj
├── Utility Library.cpp  # Minimal console entry point
├── clsUtil.h            # General-purpose helper methods
└── clsDate.h            # Date helper class used by the utilities
```

## Build and Run

The project is configured for the Visual Studio 2019 `v142` toolset and does not include a solution file.

1. Open `Utility Library.vcxproj` in Visual Studio.
2. Install v142 or retarget the project to an installed C++ toolset.
3. Build `Release | x64`.

From a Visual Studio Developer PowerShell:

```powershell
msbuild "Utility Library.vcxproj" /p:Configuration=Release /p:Platform=x64
```

## Example

```cpp
#include "clsUtil.h"

int main()
{
    clsUtil::Srand();
    int number = clsUtil::RandomNumber(1, 100);
    std::string key = clsUtil::GenerateKey(clsUtil::CapitalLetter);
}
```

## Build Verification

The project builds successfully after temporarily using the installed v145 toolset instead of the configured v142 toolset. The compiler reports warnings for extra tokens after some `#include` directives, narrowing conversions, and the enum declaration style.

## Security Note

`rand()`, the generated keys, and the character-shift functions are suitable only for learning and non-sensitive test data. They are not cryptographically secure and must not be used for passwords, tokens, encryption, or protecting real information.

## Current Scope

- The array helpers accept fixed-size C-style array signatures and require the caller to provide a valid length.
- Some names and return types can be made more precise.
- The bundled date class makes the repository broader than a focused utility-only library.
- The console program only seeds the random generator; it is not a full demonstration suite.

## Possible Improvements

- Replace `rand()` with `<random>` and clearly separate test-data generation from security APIs
- Use templates, `std::span`, or containers instead of fixed array signatures
- Correct compiler warnings and add input validation
- Move date functionality into the dedicated Date Library dependency
- Add automated tests and examples for every public helper

## Author

[Mohammad Abdelfattah](https://github.com/mohammadimad)
