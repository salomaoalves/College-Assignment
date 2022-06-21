-- Questão 1
triplo :: Int -> Int
triplo x = x*3

--Questão 2
maiorDeTres :: (Float,Float,Float) -> Float
maiorDeTres (x,y,z)
	|x>y && x>z = x
	|y>z = y
	|otherwise = z

--Questão 3
somatorio :: Int -> Int
somatorio n = sum[0..n]

--Questão 4
nEsimoTermoPA :: (Int,Int,Int) -> Int
nEsimoTermoPA (a,r,n) = a + ((n-1)*r)

--Questão 5
nEsimoTermoPG :: (Int,Int,Int) -> Int
nEsimoTermoPG (a,q,n) = a*(q^(n-1))

--Questão 6
nEsimoTermoPA :: (Int,Int,Int) -> Int
nEsimoTermoPA (a,r,n) = a + ((n-1)*r)
somaPA :: (Int,Int,Int) -> Int
somaPA (a,r,n)
    |n==1 = a
    |otherwise = nEsimoTermoPA(a,r,n) + somaPA(a,r,(n-1))

--Questão 7
nEsimoTermoPG :: (Int,Int,Int) -> Int
nEsimoTermoPG (a,q,n) = a*(q^(n-1))
somaPG :: (Int,Int,Int) -> Int
somaPG (a,q,n)
    |n==1 = a
    |otherwise = nEsimoTermoPG(a,q,n) + somaPG(a,q,(n-1))

--Questão 8
fib :: Int -> Int
fib n
    |n == 1 = 1
    |n == 2 = 1
    |otherwise = fib(n-1) + fib(n-2)

--Questão 9
anoBi :: Int -> Bool
anoBi x
   |mod x 400 == 0 = True
   |mod x 100 == 0 || mod x 4 /= 0 = False
   |otherwise = True

--Questão 10
primo :: Int -> Bool
primo n
    |(fatores n) == [1,n] = True
    |otherwise = False
fatores :: Int -> [Int]
fatores n = [x | x<-[1..n],mod n x == 0]

--Questão 11
eMaiuscula :: Char -> Bool
eMaiuscula x = not(isLower x) --necessario usar: import Data.char

--Questão 12
eMinuscula :: Char -> Bool
eMinuscula x
   |'a'<= x && x<='z' = True
   |otherwise = False

--Questão 13
eDigito :: Char -> Bool
eDigito x = isDigit x

--Questão 14
repete :: String -> Int -> String
repete x n
    |n == 0 = []
    |otherwise = x ++ repete x (n-1)

--Questão 15
branco :: Int -> String
branco n
    |n == 0 = []
    |otherwise = " " ++ branco (n-1)
branco n = repete "240" n --240 é codigo de espaço na ASCII

--Questão 16
maiorDeTres :: (Int,Int,Int) -> [Int]
maiorDeTres (x,y,z)
    |x>y && x>z = [x]
    |y>z = [y]
    |otherwise = [z]
menorDeTres :: (Int,Int,Int) -> [Int]
menorDeTres (x,y,z)
    |x<y && x<z = [x]
    |y<z = [y]
    |otherwise = [z]
parFormado :: (Int,Int,Int) -> [Int]
parFormado (x,y,z) = menorDeTres(x,y,z) ++ maiorDeTres(x,y,z)

--Questão 17
mdc :: (Int,Int) -> Int
mdc(a,b)
    |a==b = a
    |b>a = mdc(b,a)
    |otherwise = mdc(a-b,b)

--Questão 18
maiorDeTres :: (Int,Int,Int) -> (Int)
maiorDeTres (x,y,z)
    |x>y && x>z = (x)
    |y>z = (y)
    |otherwise = (z)
menorDeTres :: (Int,Int,Int) -> (Int)
menorDeTres (x,y,z)
    |x<y && x<z = (x)
    |y<z = (y)
    |otherwise = (z)
meioDeTres :: (Int,Int,Int) -> (Int)
meioDeTres (x,y,z)
    |x<y && x>z || x>y && x<z = (x)
    |y<x && y>z || y>x && y<z = (y)
    |otherwise = (z)
crescente :: (Int,Int,Int) -> (Int,Int,Int)
crescente (x,y,z) = (menorDeTres(x,y,z),meioDeTres(x,y,z),maiorDeTres(x,y,z))