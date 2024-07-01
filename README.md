# 201700490_EDD_Practica
# Manual Técnico

## Tabla de Contenidos
1. [Introducción](#introducción)
2. [Requisitos del Sistema](#requisitos-del-sistema)
3. [Instalación](#instalación)
4. [Configuración](#configuración)

## Introducción
Sistema de Gestion de Aeropueto utilizando comandos por consola. 
El sistema permite llevar el control de aviones, pasajeros y equipaje; almacenando
cada tipo en distintos tipos de estructuras de datos para su eficiencia.

## Requisitos del Sistema
- C++ 13.2.0
- json.hpp 3.11.3
- Graphviz 2.46.1

### Hardware
- CPU: 1.6 GHz
- RAM: 1 Gb
- Espacio en Disco: 100 Mb

### Software
- Sistema Operativo: Compatible con compilador de c++

## Instalación
Clonar el repositorio en carpeta local, compilar el archivo main.cpp

### Descarga
Desde el repositorio indicado

### Procedimiento de Instalación
1. Paso 1: Clonar el repositorio de descargarlo en .rar
2. Paso 2: Compilar el archivo main.cpp
3. Paso 3: cargar archivos json para la lectura de los datos

## Configuración
Los archivos json deben llamarse:
-aviones.json el cual contiene el siguiente formato:
    {
        "vuelo": "V702",
        "numero_de_registro": "N70002",
        "modelo": "Airbus A320",
        "capacidad": 150,
        "aerolinea": "AirlineY",
        "ciudad_destino": "Barcelona",
        "estado": "Disponible"
    }
-Pilotos:
    {
        "nombre": "John Doe",
        "nacionalidad": "Estados Unidos",
        "numero_de_id": "X10000123",
        "vuelo": "V715",
        "horas_de_vuelo": 300,
        "tipo_de_licencia": "PPL"
    }
-Moviemientos
MantenimientoAviones,Ingreso,N70014;
MantenimientoAviones,Salida,N70015;
DarDeBaja(X07000123);
DarDeBaja(X10000123);

-Rutas
Girona/Madrid/23;
Madrid/Girona/26;
Madrid/Barcelona/21;
Barcelona/Madrid/35;
Barcelona/Zaragoza/30;
