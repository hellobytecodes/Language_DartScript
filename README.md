# Language_DartScript
The Software-Defined Rubber Ducky. Write and execute BadUSB payloads with a simple 50-command syntax without spending hundreds on hardware.

```markdown
# DartScript - The Software-Defined BadUSB Language

**DartScript** is a fast, lightweight, and interpreter-based scripting language designed for **Windows automation** and **security testing**.
No hardware required — write and execute powerful payloads directly on any Windows machine.

---

## About the Creator

DartScript was built entirely by a **single developer**:
- **Age:** 18
- **Country:** Iran
- **Developed with:** C programming language + AI assistance
- **Initial Release:** 2026

This project is a solo effort — from the core interpreter logic to the standalone EXE compiler — built with passion for low-level programming and offensive security research.

---

## Why DartScript?

| Feature | USB Rubber Ducky | DartScript |
|--------:|:----------------:|:-----------|
| Hardware Required | Yes ($100+) | **No** |
| Execution Speed | Medium | **Fast (Native C Interpreter)** |
| Syntax Commands | ~30 | **50+** |
| Script File Extension | `.txt` | **`.drs`** |
| Compile to `.exe` | ❌ | **Yes (AOT Compiler)** |
| Learning Curve | Medium | **Easy** |
| Open Source | ❌ | **Yes (Full Source on GitHub)** |
| Built by | Hak5 Team | **Solo 18-year-old Developer** |


## Key Features

- **Pure C Interpreter:** Built from scratch in C — minimal overhead, maximum speed.
- **50+ Powerful Commands:** Covers keystroke injection, system operations, file manipulation, logic, and networking.
- **No Hardware Costs:** Turn any Windows PC into a BadUSB device.
- **Ahead-of-Time Compiler:** Compile `.drs` scripts into standalone `.exe` executables.
- **Simple Syntax:** Easy to learn, fast to write — inspired by Ducky Script but more powerful.
- **Open Source:** Full source code publicly available on GitHub.
- **Windows Only (v1.0):** The initial release targets Windows operating systems.


## Repository Structure

```

DartScript/
├── src/                    # Full interpreter source code (C)
├── App EXE/                # Pre-compiled executables (DartScript.exe + CompilerToEXE.exe)
├── docs/                   # Documentation & language reference
├── examples/               # Example .drs scripts
├── README.md
└── LICENSE

```


## Getting Started

### Run a `.drs` script directly:
```bash
DartScript.exe script.drs
```

Compile a .drs script to standalone .exe:

```bash
CompilerToEXE.exe script.drs script.exe
```

Language Documentation

<a href="">Coming Soon</a>

Installation

Two options:

Option 1: Download Pre-compiled (Recommended)

Go to the App EXE folder on the GitHub repository page and download both:

· DartScript.exe — The interpreter
· CompilerToEXE.exe — The AOT compiler

No build required. Ready to run.

Option 2: Build from Source

If you prefer to compile the language yourself, use GCC:

```bash
gcc src/main.c -o DartScript.exe -O2 -static
```

Disclaimer

This tool is intended for educational purposes, authorized penetration testing, and security research only.
Misuse of this software is strictly prohibited and punishable by law.
The author assumes no liability for any damage caused by this tool.

License

This project is licensed under the MIT License — see the LICENSE file for details.

Contact & Community

· GitHub Issues: For bug reports and feature requests.
· Discussions: Coming soon.

Built with ❤️ and C — by an 18-year-old from Iran.

```
