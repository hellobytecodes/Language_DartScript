# Dart Script - Command Reference

## Basic Commands

- **TYPE <text>** — Types text on the screen. Example: TYPE Hello World
- **TIME <milliseconds>** — Creates a delay in milliseconds. Example: TIME 1000
- **COMMENT <text>** — Writes a comment (ignored by interpreter). Example: COMMENT This is a comment
- **DEFAULT_DELAY <milliseconds>** — Sets default delay between all commands. Example: DEFAULT_DELAY 100
- **REPEAT <number>** — Repeats commands between REPEAT and END. Example: REPEAT 5 ... END
- **END** — Ends a REPEAT loop. Example: REPEAT 3 ... END

## Modifier Keys

- **PRESS <key>** — Presses a single key or combination. Examples: PRESS a, PRESS ctrl+c, PRESS alt+tab, PRESS ctrl+shift+ESC
- **WINDOWS <key>** — Windows key (can be combined). Examples: WINDOWS, WINDOWS r, WINDOWS e, WINDOWS l, WINDOWS d, WINDOWS tab
- **CONTROL <key> or CTRL <key>** — Control key combinations. Examples: CONTROL c, CONTROL v, CONTROL a, CONTROL s, CONTROL z, CONTROL f
- **ALT <key>** — Alt key combinations. Examples: ALT tab, ALT f4, ALT d
- **SHIFT <key>** — Shift key combinations. Examples: SHIFT a, SHIFT tab

## Simple Keys

- **ENTER** — Presses the Enter key. Example: ENTER
- **BACK** — Presses the Backspace key. Example: BACK
- **TAB** — Presses the Tab key. Example: TAB
- **ESC** — Presses the Escape key. Example: ESC
- **SPACE** — Presses the Space key. Example: SPACE
- **DELETE** — Presses the Delete key. Example: DELETE
- **INSERT** — Presses the Insert key. Example: INSERT

## Arrow Keys

- **UP** — Presses the Up arrow key. Example: UP
- **DOWN** — Presses the Down arrow key. Example: DOWN
- **LEFT** — Presses the Left arrow key. Example: LEFT
- **RIGHT** — Presses the Right arrow key. Example: RIGHT

## Navigation Keys

- **HOME** — Presses the Home key. Example: HOME
- **END** — Presses the End key. Example: END
- **PAGEUP** — Presses the Page Up key. Example: PAGEUP
- **PAGEDOWN** — Presses the Page Down key. Example: PAGEDOWN

## Special Keys

- **CAPS** — Toggles Caps Lock. Example: CAPS
- **PRTSC** — Takes a screenshot. Example: PRTSC
- **PAUSE** — Presses the Pause/Break key. Example: PAUSE

## Function Keys

- **F1** — Help (in most programs)
- **F2** — Rename
- **F3** — Search
- **F4** — Close tab (in browsers)
- **F5** — Refresh
- **F11** — Full screen
- **F12** — Developer Tools in browsers

## CTRL Shortcuts

- **CTRL_C** — Copy
- **CTRL_V** — Paste
- **CTRL_X** — Cut
- **CTRL_A** — Select All
- **CTRL_S** — Save
- **CTRL_Z** — Undo
- **CTRL_Y** — Redo
- **CTRL_F** — Find
- **CTRL_W** — Close Tab
- **CTRL_T** — New Tab
- **CTRL_N** — New Window
- **CTRL_P** — Print
- **CTRL_R** — Refresh
- **CTRL_E** — Search center
- **CTRL_D** — Bookmark
- **CTRL_G** — Go to Line
- **CTRL_H** — History
- **CTRL_K** — Search in Tab
- **CTRL_L** — Go to address bar

## Practical Examples

**Opening CMD:**
```

WINDOWS r
TIME 500
TYPE cmd
ENTER

```

**Opening File Explorer and navigating to C: drive:**
```

WINDOWS e
TIME 1000
ALT d
TIME 300
TYPE C:
ENTER
TIME 1000

```

**Locking the computer:**
```

WINDOWS l

```

**Opening Task Manager:**
```

PRESS ctrl+shift+ESC

```

**Taking a screenshot:**
```

WINDOWS shift+s

```

**Closing the active window:**
```

ALT f4

```

**Selecting multiple files in File Explorer:**
```

PRESS DOWN
TIME 100
PRESS shift+DOWN
TIME 100
PRESS shift+DOWN

```

**Repeat loop:**
```

REPEAT 10
PRESS DOWN
TIME 50
END

```

**Typing text and saving:**
```

TYPE Hello World
ENTER
CTRL_S
TIME 500
TYPE myfile.txt
ENTER

```

## Important Notes

1. Commands must be written in UPPERCASE (TYPE, TIME, PRESS, ...)
2. Arguments can be lowercase or uppercase
3. Use the + sign to combine keys
4. DartScript files use the .drs extension
5. To execute: DartScript.exe filename.drs

## Command Summary

| Category | Count |
|---|---|
| Basic Commands | 6 |
| Modifier Keys | 5 |
| Simple Keys | 7 |
| Arrow Keys | 4 |
| Navigation Keys | 4 |
| Special Keys | 3 |
| Function Keys | 12 |
| CTRL Shortcuts | 19 |
| **Total** | **60** |
