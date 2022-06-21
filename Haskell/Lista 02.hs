--Questão 1
criaLista :: Int -> Int -> [Int]
criaLista a b 
	|a>b = []
	|a==b = [a]
	|otherwise = [a .. b]

--Questão 2
repetidos :: [Int] -> [Int]
repetidos [] = []
repetidos (x:xs) = x:x:repetidos (xs)

--Questão 3
fatores :: Int -> [Int]
fatores n = [x | x <- [1..n],mod n x == 0]

--Questão 4
ordena :: (Ord a) => [a] -> [a]
ordena [] = []
ordena (x:xs) = insereOrd x (ordena xs)
insereOrd :: (Ord a) => a -> [a] -> [a]
insereOrd x [] = [x]
insereOrd x (y:ys)
    |x<=y = (x:y:ys)
    |otherwise = y:(insereOrd x ys)

--Questão 5

--Questão 6

--Questão 7(Obs:utiliza a questão 4)
uniao :: [Int] -> [Int] -> [Int]
uniao x y = ordena(x ++ y)

--Questão 8

--Questão 9 (Obs: igual a questão 4)
ordena :: (Ord a) => [a] -> [a]
ordena [] = []
ordena (x:xs) = insereOrd x (ordena xs)
insereOrd :: (Ord a) => a -> [a] -> [a]
insereOrd x [] = [x]
insereOrd x (y:ys)
    |x<=y = (x:y:ys)
    |otherwise = y:(insereOrd x ys)

--Questão 10 (Obs:utiliza a questão 4)
listaParaConj :: [Int] -> [Int]
listaParaConj [] = []
listaParaConj (x:xs)
    |(haRepetidos x xs) == True = listaParaConj(semRepetidos x (x:xs))
    |otherwise = ordena(x:listaParaConj xs)
haRepetidos :: Int -> [Int] -> Bool --exclusiva para este ex
haRepetidos a [] = False
haRepetidos a (x:xs)
    |a == x = True
    |otherwise = haRepetidos a xs
semRepetidos :: Int -> [Int] -> [Int]
semRepetidos a (x:xs)
    |a == x = xs
    |otherwise = x:semRepetidos a xs

--Questão 11
--a)(Obs:utiliza a questão 10 e 4)
uniaoConjA :: [Int] -> [Int] -> [Int]
uniaoConjA x y = soRepetidos(listaParaConj x ++ listaParaConj y)
soRepetidos :: [Int] -> [Int]
soRepetidos [] = []
soRepetidos (x:xs)
    |(haRepetidos x xs) == True = x:(soRepetidos xs)
    |otherwise = soRepetidos xs

--b)

--c)

--Questão 12
--a)
multiTres100a300 :: [Int]
multiTres100a300 = [a | a <- [100 .. 300], mod a 3 == 0]

--b)
fatores100 :: [Int]
fatores100 = [i | i<-[1..100],ePrimo i == True]
ePrimo :: Int -> Bool
ePrimo n
    |(fatores n) == [1,n] = True
    |otherwise = False
fatores :: Int -> [Int]
fatores n = [x | x<-[1..n],mod n x == 0]

--c)
paresAlternados :: [Int] -> [Int] -> [(Int,Int)]
paresAlternados _ [] = []
paresAlternados [] _ = []
paresAlternados (x:xs) (y:ys) = (x,y):paresAlternados xs ys

--d)
fracoes :: [Int] -> [Int] -> [String]
fracoes _ [] = []
fracoes [] _ = []
fracoes (x:xs) (y:ys) = (show(x)++"/"++show(y)):fracoes xs ys

--e)
polinomio :: [Float]
polinomio = [(i / 100)^2+7*(i / 100)+1 | i<-[0 .. 100]]

--f)
