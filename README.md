# MINI~~S~~HELL - our bash-like shell
The aim of this project is to study processes and file descriptors. The project is written using the C programming language.

## Features
Our shell can:
- Process practically an infinite number of pipes in parallel
- Work with environmental variables, including `$?`
- Search and launch the right executable using `$PATH` variable
- Store the command history in RAM
- Process both double and single quotes as well as the `;` separator
- Process `>`, `>>`, `<` redirects
- Screen the symbols with a backslash
- Process `ctrl+C`, `ctrl+D`, `ctrl+\` signals as in **Bash**
- Process following built-in commands:
   - **echo** with option `-n` 
   - **cd** with only a relative or absolute path
   - **pwd** with no options
   - **export** with no options
   - **unset** with no options
   - **env** with no options or arguments
   - **exit** with no options
   
## Usecase example
<details>
  <summary>Spoiler</summary>
  
  ```
  minihell > echo "Our shell rules!" | cat -e | cat -e
  Our shell rules!$$
  minihell > ls -la | grep minishell | wc
       1       9      61
  minihell > export | grep PATH
  declare -x PATH="/Users/cisis/.brew/opt/llvm/bin:/Users/cisis/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin"
  ```
  
</details>

## Authors
- [Vadim](https://github.com/lelderbe) - Executor (incl. FDs, pipes, built-in commands)
- [Ruslan](https://github.com/r-egorov) - CLI (incl. command history), Parser
