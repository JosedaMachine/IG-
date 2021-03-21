
Este esqueleto utiliza las librerias:
 - freeglut(x64) para la gestión de las ventanas y la libreria OpenGL
 - glml para las operaciones matématicas en CPU que siguen las especificaciones de las operaciones matemáticas en GPU de OpenGL.

Al añadir un nuevo proyecto recuerda añadir la página de propiedades ProyectosIG.props al nuevo proyecto:
Menú VER -> Otras ventanas -> Administrador de propiedades -> Agregar hoja de propiedades existente -> ProyectosIG.props -> Guardar

Para añadir una nueva libreria, copia su directorio en la solución y los bin de la libreria en el directorio bin de la solución.
Y añade los nuevos elementos al archivo ProyectosIG.props en las lineas: IncludePath, LibraryPath y AdditionalDependencies.

También puedes crear otras páginas de propiedades.