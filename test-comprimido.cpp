#define CATCH_CONFIG_MAIN

#include "lib/catch.hpp"

#include "Juego.h"

TEST_CASE("Guardar comprimido")
{
    SECTION("Partida no iniciada")
    {
        Juego juego;
        INFO("Se trata guardar una partida que no ha iniciado");

        //Se manda guardar una partida que no ha iniciado,
        //por lo que debe retornar false
        REQUIRE(!juego.guardar_comprimido(false, "partida"));
    }
    SECTION("Partida iniciada")
    {
        Juego juego;
        //Se lee un archivo con una partida ya iniciada
        juego.inicializarArchivo(false, "partida.txt");

        INFO("Se trata guardar una partida iniciada")

        //Se guarda codificada en un archivo binario
        //Si se guardó, debe retornar true
        REQUIRE(juego.guardar_comprimido(true, "partida"));  
    }
}