Tipo Abstrato de Dados
import Stack --modulo Stack
a = push 3 (push 2 (push 1 (push 0 empty)))
size :: Stack a -> Int
size s
    |isEmpty s = 0
    |otherwise = 1 + size (pop s)
-------------------------------------------------------------------
favor :: IO()
favor = do putStrLn "Escrava primeiro numero: "
           n1 <- getLine
           putStrLn "Escrava segundo numero: "
           n2 <- getLine
           putStrLn "Escrava segundo numero: "
           n3 <- getLine
           putStr "Soma eh: "
           putStrLn (show ((read n1::Float) * (read n2::Float) * (read n3::Float)))
--------------------------------------------------------------
leInt2 :: IO(Int)
leInt2 = do putStr "Digite um valor inteiro: "
            n <- getLine
            return (read n)
--------------------------------------------------------------
module Main (main) where
main :: IO()
main = do putStr "Temp: "
          f <- readLn
          print(celsius(f))
celsius :: Double -> Double
celsius a = ((5/9) * (a-32))
---------------------------------------------------------
main :: IO()
main = do putStrLn "a:"
          a <- readLn
          putStrLn "b:"
          b <- readLn
          putStrLn "c:"
          c <- readLn
          let delta = b*b-4*a*c
          putStrLn ("Delta: "++ (show delta))
          let r1 = (-b+sqrt(delta))/(2*a)
          let r2 = (-b-sqrt(delta))/(2*a)
          putStr "Raizes: "
          if delta < 0
            then putStrLn "Nao ha raizes reais"
            else putStrLn ("R1 "++show r1++" R2 "++show r2)
-----------------------------------------------------------------
main :: IO()
main = do putStrLn "Sua idade:"
          idade <- readLn
          if idade < 16
            then putStrLn "Nao eleitor"
            else if idade < 65 && idade >= 18
                then putStrLn "eleitor obrigatorio"
                else putStrLn "eleitor facultativo"
-----------------------------------------------------------------
main :: IO()
main = do putStr "Salario bruto:"
          sal <- readLn
          let por = sal * 0.3
          putStr "Valor prestacao: "
          pres <- readLn
          if por > pres
            then putStrLn "Aprovado"
            else putStrLn "Negado"
--------------------------------------------------------------------
module Main (main) where

main :: IO()
main = do putStrLn "---------------------"
          putStr "Qual seu salario"
          sal <- readLn
          putStrLn "Opções:"
          putStrLn "---------------------"
          putStrLn "1. Imposto"
          putStrLn "2. Novo salario"
          putStrLn "3. Clasificação"
          putStrLn "---------------------"
          putStrLn "Digite a opção desejada: "
          pos <- readLn
          if pos == 1
            then posicao1(sal)
            else if pos == 2
                then posicao2(sal)
                else if pos == 3
                    then posicao3(sal)
                    else putStrLn "Possibilidade invalida"
------------------------------------------------------------------
posicao1 :: Float -> IO()
posicao1 sal
    |sal < 500 = putStrLn "5%"
    |sal > 850 = putStrLn "10%"
    |otherwise = putStrLn "15%"

posicao2 :: Float -> IO()
posicao2 sal
    |sal > 1500 = putStrLn "R$25"
    |sal < 450 = putStrLn "R$100"
    |sal >= 750 && sal <= 1500 = putStrLn "R$50"
    |otherwise = putStrLn "R$75"

posicao3 :: Float -> IO()
posicao3 sal
    |sal <= 750 = putStrLn "mal remunerado"
    |otherwise = putStrLn "bem remunerado"
-----------------------------------------------------------
