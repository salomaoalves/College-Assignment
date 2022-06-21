--Questão 02:
data NomeP = Nome String
    deriving (Show,Eq)
data SobreNomeP = SobreNome String 
    deriving (Show,Eq)
type NomeCompleto = (NomeP,SobreNomeP)
compara :: NomeCompleto -> NomeCompleto -> String
compara (x,x1) (y,y1)
    |(comparaNome x y) == True && (comparaSobrenome x1 y1) == True = "nome e sobrenome são iguais"
    |(comparaNome x y) == True && (comparaSobrenome x1 y1) == False = "nome são iguais"
    |(comparaNome x y) == False && (comparaSobrenome x1 y1) == True = "sobrenome são iguais"
    otherwise = "nome e sobrenome são iguais"
comparaNome :: NomeP -> NomeP -> Bool
comparaNome x y
    |x == y = True
    |otherwise = False
comparaSobrenome ::SobreNomeP -> SobreNomeP -> Bool
comparaSobrenome x1 y1
    |x1 == y1 = True
    |otherwise = False

--Questão 03:

--Questão 04:
data LL = Latitude Int Int Int | Longitude Int Int Int 
    deriving (Eq)
instance Show LL where
 show (Latitude a b c) = "Lat " ++ (show (a))++"°" ++ (show (b))++"'"++ (show (c))++"''"
 show (Longitude a b c) = "Long " ++ (show (a))++"°" ++ (show (b))++"'"++ (show (c))++"''"
type PosicaoLocal = (String, LL, LL)
type Cidades = [PosicaoLocal]
--a)
c1,c2::PosicaoLocal
c1 = ("Brasilia", Latitude (-15) 46 47, Longitude 47 55 47)
c2 = ("Uberlandia", Latitude (-18) 55 07, Longitude 48 16 38)
eLat :: PosicaoLocal->(String,LL)
eLat (p,(Latitude a b c),(Longitude x y z)) = (p,(Latitude a b c))
eLong ::PosicaoLocal -> (String,LL)
eLong (p,(Latitude a b c),(Longitude x y z)) = (p,(Longitude x y z))
--b)
norteDe::PosicaoLocal->PosicaoLocal->Bool
norteDe (p,(Latitude a b c),(Longitude x y z)) (p1,(Latitude a1 b1 c1),(Longitude x1 y1 z1))
    |a > a1 = True
    |a1 > a = False
    |b > b1 = True
    |b1 > b = False
    |c > c1 = True
    |otherwise = False
--c)
lcidades::Cidades
lcidades =
       [("Rio Branco", Latitude 09 58 29, Longitude 67 48 36),
        ("Brasilia", Latitude (-15) 46 47, Longitude 47 55 47),
        ("Torres", Latitude (-29) 20 07, Longitude 49 43 37),
        ("Joao Pessoa", Latitude (-07) 06 54, Longitude 34 51 47),
        ("Uberlandia", Latitude (-43) 55 07, Longitude 48 16 38)]
--c.1)
baixoEquador :: Cidades -> Int
baixoEquador [] = 0
baixoEquador ((p,(Latitude a b c),(Longitude x y z)):xs)
    |a < 0 = 1 + baixoEquador xs
    |b < 0 = 1 + baixoEquador xs
    |c < 0 = 1 + baixoEquador xs
    |otherwise = baixoEquador xs
--c.2)
entre40e50 :: Cidades -> Int
entre40e50 [] = 0
entre40e50 ((p,(Latitude a b c),(Longitude x y z)):xs)
    |(x >= 40 && x <= 50) || (x <= -40 && x >= -50) = 1 + entre40e50 xs
    |otherwise = entre40e50 xs

--Questão 05:
    --O tipo Talvez pode retornar o Valor mais um a, q deve ser
        --definido na função q usá-lo, ou então o Nada; se chamar
        --'>divisaoSegura 5 0' devolve 'Nada'
        --'>devisaoSegura 5 4' devolve 'Valor 1.25'
data Talvez a = Valor a | Nada
    deriving (Show)
divisaoSegura :: Float -> Float -> Talvez Float
divisaoSegura x y = if y == 0 then Nada else Valor (x/y)

--Questão 06:
addPares :: [(Int,Int)] -> [Int]
addPares lista = [ m+n | (m,n) <- lista ]
--a)
addParesT :: [(Int,Int)] -> [Int]
addParesT l = [ m+n | (m,n)<-l, m<n]
--b)
addParesL :: [(Int,Int)] -> [Int]
addParesL [] = []
addParesL ((a,b):zs) = [(\x -> (\y -> x+y)) a b] ++ (addParesL zs)
--c)
eMenor :: (Int,Int) -> Bool
eMenor (a,b)
    |a < b = True
    |otherwise = False
addParesTL :: [(Int,Int)] -> [Int]
addParesTL l = map (\(x,y) -> x+y) (filter eMenor l)

--Questão 07:
    --O mp pega os primeiros elementos das duas listas, aplica a função
        --f nesses dois, depois, por meio da recursividade, faz isso c/
        --os prox. elementos, até uma das duas listas acabar
mp f [] ys = []
mp f xs [] = []
mp f (x:xs) (y:ys) = f x y : mp f xs ys

--Questão 08:
somaQuad :: Int -> Int
somaQuad n = foldr1 (+) (map (^2) [0..n])

--Questão 09:
ePos :: Int -> Bool
ePos n
    |n > 0 = True
    |otherwise = False
somaQuadPos :: [Int] -> Int
somaQuadPos l = foldr1 (+) (map (^2) (filter ePos l))

--Questão 10:
    --A misterio irá receber uma lista xs, primeiro ele irá mapear a 
        --lista xs, com  auxilio da função de ordem superior map, de
        --modo que gera uma lista de lista, onde cada elemento é uma
        --lista, dpois ele ira reduzi-lá para uma única lista, com o
        --auxilo da função de ordem superior forldr, ela irá contatenar
        --cada elemento numa unica lista
fun :: Int -> [Int]
fun x = [x]
misterio :: [Int] -> [Int]
misterio xs = foldr (++) [] (map fun xs)