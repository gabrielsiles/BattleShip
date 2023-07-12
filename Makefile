# Compilateur
CC = gcc

# Flags du compilateur
CFLAGS = -Wall -Wextra -I/opt/homebrew/Cellar/cunit/2.1-3/include/

# Répertoire des fichiers d'en-tête de CUnit
CUNIT_LIB_DIR = /opt/homebrew/Cellar/cunit/2.1-3/lib/

# Fichiers source
SRCS = main.c bataille_navale.c statistiques.c sauvegarder_partie.c
TEST_SRCS = cunit_test.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(filter-out main.o, $(OBJS)) $(TEST_SRCS:.c=.o)

# Fichier exécutable
TARGET = bataille_navale
TEST_TARGET = test_cunit

# Cible par défaut
all: $(TARGET)

# Compilation des fichiers source en fichiers objets
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Lien des fichiers objets en un exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Lien des fichiers objets du tests runner en un exécutable de tests
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(CUNIT_LIB_DIR) -lcunit

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Exécution du programme avec génération des statistiques
stats: $(TARGET)
	./$(TARGET) -S stats.txt

# Compilation des tests CUnit et bats
test: $(TEST_TARGET)
	./$(TEST_TARGET)
	bats check.bats

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET) $(OBJS) $(TEST_TARGET) $(TEST_OBJS:.c=.o)

# Cible pour générer une version HTML du README.md
html:
	pandoc README.md -o README.html
