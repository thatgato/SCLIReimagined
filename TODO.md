# General TODO for this project

## Functionality

- Value registers that persist across different commands
- File value registers (registers that persist across different sessions, by saving data to files)
- Benchmarked calculations
- Look into the LineNoise library suggested by ChatGPT for autocompletion
- Constants library (Get them using commands, or possibly an expression parser...?)
- A separate .exe for the logging console, as the current one's capabilities are very lacking, ex.: we can't even print
  multi-line logs

## UI

- Progress bars and/or calculation animations for more complex things (although everything should finish basically
  before the user can press enter...)
- Different types of states displayed on the console

- Register UI (example below, register functionality will be explained later on)

``` 
> set a = 3.1415
> set b = 2.718
> compute a * b
[Result] 8.5392
> registers
╭────────────┬───────────╮
│ Register   │ Value     │
├────────────┼───────────┤
│ a          │ 3.1415    │
│ b          │ 2.718     │
│ last       │ 8.5392    │
╰────────────┴───────────╯
```

- File Register UI (Very similar to the normal register UI)

- Units (m/s, km/h, etc.)
