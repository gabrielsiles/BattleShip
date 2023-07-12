
#!/usr/bin/env bats



@test "Dimension de carte invalide" {
  run cat tests/test0
  expected_output='Veuillez entrer la taille de la carte (minimum 6, maximum 100) : 5
Taille de carte invalide. Veuillez entrer une taille entre 6 et 100.'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}


@test "Dimension de carte valide" {
  run cat tests/test1
  expected_output='Veuillez entrer la taille de la carte (minimum 6, maximum 100) : 6
Entrez une position pour X:'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

@test "Position invalide" {
  run cat tests/test2
  expected_output='Entrez une position pour X: -1
Position invalide. Veuillez entrer une position entre 0 et 5.'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

@test "Position valide" {
  run cat tests/test3
  expected_output='Entrez une position pour X: 1
Entrez une position pour Y: 1
Coup 1 : (1, 1)'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

@test "Coup Touché" {
  run cat tests/test4
  expected_output='Entrez une position pour X: 1
Entrez une position pour Y: 1
Coup 1 : (1, 1)
Touché !
. . . . . .
. x . . . .
. . . . . .
. . . . . .
. . . . . .
. . . . . .'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}


@test "Coup À l'eau" {
  run cat tests/test5
  expected_output='Entrez une position pour X: 1
Entrez une position pour Y: 1
Coup 1 : (1, 1)
À l eau.
. . . . . .
. o . . . .
. . . . . .
. . . . . .
. . . . . .
. . . . . .'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

@test "Coup Déjà joué" {
  run cat tests/test6
  expected_output='Veuillez entrer la taille de la carte (minimum 6, maximum 100) : 6
Entrez une position pour X: 1
Entrez une position pour Y: 1
Coup 1 : (1, 1)
Touché !
. . . . . .
. x . . . .
. . . . . .
. . . . . .
. . . . . .
. . . . . .
Entrez une position pour X: 1
Entrez une position pour Y: 1
Déjà joué.
Coup 2 : (1, 1)'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

@test "Coup pour bateau couler" {
  run cat tests/test7
  expected_output='Touché !
Navire Contre-torpilleur 1 de taille 3 coulé !
o o x x x x
. . . . . .
. . . . . .
. . . . . .
. . . . . .
. . . . . .'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

@test "Fin de partie - Victoire" {
  run cat tests/test8
  expected_output='o o x x x x
o o x o o x
o o x o o x
x o x o o x
x o o o o o
o x x x x x
Bravo !! Vous avez gagné en 36 coups.'
  [ "$status" -eq 0 ]
  [ "$output" = "$expected_output" ]
}

