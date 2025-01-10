#!/bin/bash

# Création de l'image et démarrage du conteneur
up() {
    docker-compose up -d --build
}

# Arrêt du conteneur
down() {
    docker-compose down
}

# Accès au shell du conteneur
shell() {
    docker-compose exec libftpp /bin/bash
}

# Compilation du projet
build() {
    docker-compose exec libftpp make
}

# Nettoyage
clean() {
    docker-compose exec libftpp make fclean
}

# Tests
test() {
    docker-compose exec libftpp make test
}

case "$1" in
    "up")
        up
        ;;
    "down")
        down
        ;;
    "shell")
        shell
        ;;
    "build")
        build
        ;;
    "clean")
        clean
        ;;
    "test")
        test
        ;;
    *)
        echo "Usage: $0 {up|down|shell|build|clean|test}"
        exit 1
        ;;
esac