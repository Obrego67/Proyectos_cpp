import os

# Obtener la carpeta raíz del proyecto
proyecto = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

nombre = input("Nombre de la clase: ").strip()

if not nombre.isidentifier():
    print("Nombre no válido")
    exit()

h = os.path.join(proyecto, "src", "headers")
c = os.path.join(proyecto, "src", "source")

header = os.path.join(h, nombre + ".h")
source = os.path.join(c, nombre + ".cpp")

if os.path.exists(header) or os.path.exists(source):
    print("Ya existe alguno de los archivos")
    exit()

guard = nombre.upper() + "_H"

with open(header, "w", encoding="utf-8") as f:
    f.write(f"""#ifndef {guard}
#define {guard}

class {nombre} {{
public:
    {nombre}();
    ~{nombre}();

private:

}};

#endif
""")

with open(source, "w", encoding="utf-8") as f:
    f.write(f"""#include "{nombre}.h"
""")

print("Clase creada correctamente:")
print(header)
print(source)