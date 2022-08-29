Contributing
============

Getting started
---------------
To get started you will need the following software installed:

- [Visual Studio Code](https://code.visualstudio.com/)
- [Git](https://git-scm.com/)
- Clang-Format (Bundled with 'Clang' - probably already installed on your system)

You will also need the following VSCode extensions:

- [PROS-VSC](https://marketplace.visualstudio.com/items?itemName=sigbots.pros) (This includes the PROS executable)
- [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) (Requires Clang-Format to be installed seperately)

After installing the necessary software, properly set up git on your machine and clone this project using `git clone <URI>`.

From there, in the project directory, create a file at `.vscode/settings.json` with the following entries:

```json
{
	"editor.formatOnSave": true,
    "editor.detectIndentation": false,
    "editor.insertSpaces": false,
    "editor.defaultFormatter": "xaver.clang-format",
	"clang-format.style": "file",
}
```

Now, upon saving files, your code will be properly formatted for consistency. You are now ready to modify files in this project.

Building
--------
To build, you may run `make` and then `pros upload` to download to the brain, or you can run the `build.sh` script to do that for you automatically.