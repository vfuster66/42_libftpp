# libftpp - Advanced C++ Library

## Description
A comprehensive C++ toolbox implementing various design patterns, data structures, and utilities.

## Environment Setup

### Prerequisites
- Docker
- Docker Compose

### First Time Setup
```bash
# Give execution permission to the development script
chmod +x dev.sh

# Build and start the Docker container
./dev.sh up

# Access the container shell
./dev.sh shell

# Compile the library
make

# Clean object files
make clean

# Clean everything (objects and library)
make fclean

# Recompile everything
make re

# Run tests
make test

# Exit the container shell
exit

# Stop the Docker container
./dev.sh dev down
```

### Script Commands Reference

```bash
./dev.sh up - Start the container
./dev.sh down - Stop the container
./dev.sh shell - Access container shell
./dev.sh build - Run make inside container
./dev.sh clean - Run make clean inside container
./dev.sh test - Run tests inside container
```

### Development Workflow

1. Start a working session:


- Run 
```
chmod +x dev.sh
````
to make script executable
- Start container with ./dev.sh up
- Access container shell with ./dev.sh shell


2. Inside the container, use Make commands:


- make - Compile the library
- make clean - Clean object files
- make fclean - Clean everything (objects and library)
- make re - Recompile everything
- make test - Run tests


3. End a working session:


 - Exit container shell with exit
 - Stop container with ./dev.sh down

### Project structure
```
libftpp/
├── include/             # Header files
│   ├── data_structures/
│   ├── design_patterns/
│   ├── threading/
│   ├── network/
│   └── mathematics/
├── src/                # Source files
├── tests/             # Test files
└── libftpp.hpp        # Main header
```

## Structures de données

### Pool
- Gestion de pool d'objets réutilisables 
- Allocation préalable avec `resize()`
- Acquisition d'objets avec `acquire()`
- Libération automatique via Pool::Object

### DataBuffer
- Conteneur polymorphique pour stocker des objets en format binaire
- Sérialisation/désérialisation via les opérateurs << et >>  
- Support des types de base et personnalisés

## Design Patterns

### Memento
- Sauvegarde et restauration d'état d'objets
- Méthode `save()` pour créer un instantané
- Méthode `load()` pour restaurer un état précédent

### Observer
- Système de souscription à des événements
- Notification des observateurs lors de changements 
- Support des callbacks personnalisés

### Singleton
- Garantit une instance unique par classe
- Accès global via `instance()`
- Instantiation avec paramètres variables 

### StateMachine
- Gestion d'états et de transitions
- Actions associées aux états
- Transitions conditionnelles entre états

## Threading

### ThreadSafeQueue 
- File thread-safe
- Opérations push_front/back et pop_front/back
- Protection contre les accès concurrents

### Thread
- Wrapper pour std::thread avec nom
- Démarrage/arrêt contrôlés  
- Intégration avec ThreadSafeIOStream

### WorkerPool
- Pool de threads workers
- Distribution automatique des tâches
- Gestion efficace des ressources

### PersistentWorker
- Exécution continue de tâches
- Ajout/suppression dynamique de tâches
- Thread-safe

### ThreadSafeIOStream
- Version thread-safe de iostream
- Support des préfixes par thread
- Sortie synchronisée

## Network

### Message
- Communication entre client et serveur
- Types de messages personnalisables
- Sérialisation intégrée

### Client
- Connexion à un serveur
- Envoi/réception asynchrone de messages
- Callbacks pour les types de messages

### Server 
- Gestion multiple clients
- Routage des messages 
- Actions par type de message

## Mathematics

### IVector2/IVector3
- Vecteurs 2D/3D templatés
- Opérations vectorielles complètes
- Calculs de longueur, normalisation, produit scalaire/vectoriel

### PerlinNoise2D
- Génération de bruit de Perlin 2D
- Interpolation lisse
- Paramètres configurables

### Random2DCoordinateGenerator
- Génération de nombres pseudo-aléatoires basés sur coordonnées
- Résultats déterministes
- Seed configurable

## Bonus

### Timer
- Gestion de durées
- Vérification de timeout
- Précision milliseconde

### Chronometer
- Mesure de durées
- Précision haute résolution
- Interface start/stop/reset

### Application/Widget
- Framework UI simple
- Gestion de widgets
- Événements de clic

### ObservableValue
- Valeurs observables
- Notifications de changement
- Support multiple observateurs

### Logger
- Système de logging multiniveau 
- Timestamps automatiques
- Filtrage par niveau de sévérité