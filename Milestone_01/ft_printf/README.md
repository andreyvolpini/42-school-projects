## How to use this project

```bash
make
./ft_printf "Hello %s\n" "42!"

## Outros comandos
make clean    # Removes all object files (*.o) generated during compilation
make fclean   # Removes all object files and the executable produced by the build
make re       # Runs `make fclean` followed by `make` to rebuild everything from scratch
