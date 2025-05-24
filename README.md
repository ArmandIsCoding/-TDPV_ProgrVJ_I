
# 🎮 Programación de Videojuegos I - TDPV_ProgrVJ_I

**Programación de Videojuegos 1 - UNL FICH**  
🚀 *Desarrollado en SFML*  

## 📌 Descripción

Este proyecto es parte de la materia *Programación de Videojuegos 1* de la **Universidad Nacional del Litoral - FICH**. Se trata de una implementación en **SFML**, permitiendo la animación de un personaje con distintas acciones como caminar, correr, saltar y escalar.  
💡 **Objetivo:** Aprender y aplicar los principios de la programación de videojuegos con SFML.
💡 **Acerca de la carrera:** https://www.unl.edu.ar/carreras/tecnicatura-en-diseno-y-programacion-de-videojuegos-2/.

## 🎮 Características

✔️ Movimiento con teclas `A`, `D`, `W`, `S`  
✔️ Animaciones (`idle`, `run`, `stairs`, `falls of`, `jump`)  
✔️ Salto con `Barra Espaciadora` y caída con gravedad  
✔️ Fondo con imagen personalizada (`assets/background.png`)  
✔️ Escalado y rotación del personaje con `Z`, `X`, `R`, `Q`  
✔️ Estructura optimizada para futuras mejoras  

## 🛠️ Tecnologías

- 🖥️ **SFML** - Biblioteca para gráficos y animaciones  
- 🔗 **C++** - Lenguaje de programación  
- 🎨 **Afichmation** - Manejador de animaciones, clase provista por la cátedra. Créditos: https://github.com/nicolastuka/Afichmation 

## ⚡ Controles (no todos implementados aún)

| 🎮 Acción          | ⌨️ Tecla |
|-------------------|----------|
| Izquierda        | `A`      |
| Derecha          | `D`      |
| Subir escaleras  | `W`      |
| Caer             | `S`      |
| Saltar           | `ESPACIO` |
| Volver a idle    | Soltar teclas |
| Escalar objeto   | `Z` `X`  |
| Rotar personaje  | `R` `Q`  |


## 📂 Estructura de Archivos
```
📁 Proyecto
│── 🎨 assets/
│     ├── spritesheet.png
│     ├── background.png
│── 📜 Afichmation.h
│── 📜 main.cpp
│── 📜 README.md
```

## 📝 Instalación y Uso

1️⃣ Clonar el repositorio:  
```sh
git clone https://github.com/tuusuario/TDPV_ProgrVJ_I.git
```

2️⃣ Instalar SFML y compilar el proyecto:  
```sh
g++ main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
```

3️⃣ Ejecutar el juego:  
```sh
./game
```

## 🤝 Contribuciones
Si quieres mejorar este proyecto, ¡será bienvenido!  
📌 **Cualquier sugerencia o PR** puede ser enviado al repo.
📢 *Desarrollado con pasión por Armando.Meabe at gmail dot com en Programación de Videojuegos I - UNL FICH*

## 📜 Licencia
Ni idea, este proyecto es de uso académico y educativo.  

💡 **MTFBWY! 🚀**
