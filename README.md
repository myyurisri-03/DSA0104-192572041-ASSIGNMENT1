# DSA01-<RegisterNumber>-Assignment1

**Name:** Myyuri  **Register number:** <RegisterNumber>
**Compiler:** g++ (Ubuntu 13.3.0) 13.3.0
**Compile command (every program):** `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>`
**Run:** `./<name>` (Task08: `./input_cin < input_bad.txt`, `./input_getline < input_bad2.txt`; Task11: run inside the folder so `fares.cfg` is found)

| Folder | Programs | Result |
|---|---|---|
| Task01 | (analysis only - see report; UML in `diagrams/`) | Objects, rules, assumptions listed |
| Task02 | `constants.h`, `constants_demo.cpp`, `enum_error.cpp` | Macro gives 15, constexpr gives 20; enum class blocks int conversion |
| Task03 | `types_demo.cpp`, `double_error_growth.cpp` | Day total 10,800,000,000 paise overflows int; double drifts, paise exact |
| Task04 | `predict.cpp`, `conversions_fixed.cpp`, `narrowing_error.cpp` | `3 3.5 / C 68 / 1 true / s >= u`; explicit casts fix signed/unsigned |
| Task05 | `predict.cpp`, `peak_table.cpp`, `postfix_demo.cpp` | `11 16 / 9 6 4 / 6 4 / 3 1 -3 -1 / 18`; table == expression |
| Task06 | `complete_code.cpp`, `boundary_hours.cpp`, `fare_array_lookup.cpp` | Matches expected output; 8:00/17:00 peak, 10:00/20:00 off-peak |
| Task07 | `procedural.cpp`, `oop.cpp`, `public_balance.cpp` | Class blocks negative balance; public member does not |
| Task08 | `input_cin.cpp`, `input_getline.cpp`, `input_bad*.txt` | Recovers from letters / out-of-range input |
| Task09 | `fare_system.cpp` | 19 / 19 tests pass |
| Task10 | `totals.cpp`, `warnings_demo.cpp` | int overflows at journey 1,301,506; float drifts at 3M |
| Task11 | `config_fares.cpp`, `fares.cfg` | 4 fares read in ~80 microseconds |
| Task12 | `original_cannot_absorb.cpp`, `revised_design.cpp` | Old design fails; revised passes 14 / 14 |

Output screenshots: add your own terminal screenshots into each task folder (`*_output.txt` files hold the captured text).
