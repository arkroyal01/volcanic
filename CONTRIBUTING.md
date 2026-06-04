# Contributing to Volcanic

## What Needs Doing

You can open issues for Volcanic on our [issue tracker](https://github.com/arkroyal01/volcanic/issues).

## Where Stuff Is

Everything codewise for Volcanic itself is located in the `src` directory.

### Settings Pages / KCMs

The configuration modules live in `src/kcmkwin`. They are currently a
**work in progress**: Volcanic builds with `KWIN_BUILD_KCMS=OFF` (the KDE
System Settings KCMs pull in the kcmutils/knewstuff/kio stack we are shedding),
so they are not built by default. The plan is to replace them with lightweight
**GTK2 applets** for configuration under the LXDE shell; the `src/kcmkwin`
sources remain in the meantime.

### Default Decorations

The default window decoration is **Breeze**, shipped via the standalone
`breeze-decoration` package — just Breeze's `kdecoration` un-bundled from the
full Breeze (style/KCM/colorschemes). Volcanic does not carry the decoration
itself; the source is in the [Breeze repository](https://invent.kde.org/plasma/breeze), in `kdecoration`.

### Tab Switcher

The default visual appearance of the tab switcher is located in `src/tabbox/switchers`.

Other window switchers historically shipped by default come from [Plasma Addons](https://invent.kde.org/plasma/kdeplasma-addons) (`kwin/windowswitchers`); those pull the Plasma/QML stack Volcanic is moving away from.

### Window Management

Most window management stuff (layouting, movement, properties, communication between client<->server) is defined in files ending with `client`, such as `x11client.cpp` and `xdgshellclient.cpp`.

### Window Effects

Window effects are located in `src/plugins`, one effect plugin per folder.  Folder `src/plugins/private` contains the plugin (`org.kde.kwin_x11.private.effects`) that exposes layouting properties and `WindowHeap.qml` for QML effects.  Not everything here is an effect as exposed in the configuration UI, such as the colour picker in `src/plugins/colorpicker`.

Of note, the Effects QML engine is shared with the Scripting components (see `src/scripting`).

### Scripting API

Many objects in Volcanic are exposed directly to the scripting API; scriptable properties are marked with Q_PROPERTY and functions that scripts can invoke on them.

Other scripting stuff is located in `src/scripting`.

## Conventions

### Coding Conventions

We follow Volcanic's coding conventions which are located in the [coding-conventions](doc/coding-conventions.md) document.

We additionally follow [KDE's Frameworks Coding Style](https://community.kde.org/Policies/Frameworks_Coding_Style).

### Commits

We usually use this convention for commits in Volcanic:

```git
component/subcomponent: Do a thing

This is a body of the commit message,
elaborating on why we're doing thing.
```

While this isn't a hard rule, it's appreciated for easy scanning of commits by their messages.

## Contributing

Volcanic uses its [GitHub repository](https://github.com/arkroyal01/volcanic) for submitting code.

It's just a matter of forking the repository and then doing a pull request with your changes.

## Running Volcanic From Source

Volcanic uses CMake, so you can build it like this:

```bash
mkdir _build
cd _build
cmake ..
make
```

Once built, you can either install it over your system install (not recommended) or run it from the build directory directly.

The binary is still named `kwin_x11` (the identity rename is a later step). To run it from your build directory, replacing the current instance in your X11 session:

```bash
# from the root of your build directory
source prefix.sh
cd bin
env QT_PLUGIN_PATH="$(pwd)":"$QT_PLUGIN_PATH" ./kwin_x11 --replace
```

`QT_PLUGIN_PATH` tells Qt to load Volcanic's plugins from the build directory, and not from your system install.

To test in isolation without disturbing your running session, launch a nested instance inside its own D-Bus session (`dbus-run-session`) so it doesn't conflict over bus object exports or global shortcuts.

In a normal install, Volcanic runs as the LXDE session's window manager
(`window_manager=kwin_x11` in `~/.config/lxsession/LXDE/desktop.conf`).

## Using A Debugger

Trying to attach a debugger to a running Volcanic instance from within itself will likely be the last thing you do in the session, as Volcanic will freeze until you resume it from your debugger, which you need Volcanic to interact with.

Instead, either attach a debugger to a nested Volcanic instance or debug over SSH.

## Tests

Volcanic has a series of unit tests and integration tests that ensure everything is running as expected.

If you're adding substantial new code, it's expected that you'll write tests for it to ensure that it's working as expected.

If you're fixing a bug, it's appreciated, but not expected, that you add a test case for the bug you fix.
