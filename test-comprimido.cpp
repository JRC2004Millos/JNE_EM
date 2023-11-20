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

TEST_CASE("Costo conquista")
{
    SECTION("Partida no iniciada")
    {
        Juego juego;
        INFO("Se trata pedir el costo de una conquista en una partida que no se ha inicializado");

        //Se le indica que la partida no ha iniciado,
        //por lo que debería retornar false
        REQUIRE(!juego.costo_conquista(false, "jugador1"));
    }
    SECTION("Partida que ya obtuvo un ganador")
    {
        Juego juego;
        INFO("Se carga una partida que ya fue ganada y se pide el costo de conquista");
        juego.inicializarArchivo(false, "partidaGanada.txt");

        //Debe retornar false debido a que la partida ya tuvo un ganador
        REQUIRE(!juego.costo_conquista(true, "egipto"));
    }
    SECTION("Comando correcto")
    {
        Juego juego;
        INFO("Se carga una partida en juego y un jugador pide el costo de una conquista");
        juego.inicializarArchivo(false, "partida.txt");

        //Debe retornar true, flujo correcto
        REQUIRE(juego.costo_conquista(true, "egipto"));

    }
}