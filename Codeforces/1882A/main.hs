{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
import Data.Char
import Control.Monad

chi = (toInteger . ord)

func :: String -> Integer -> [String]
func "" n = [[]]
func chs 0 = [[]]
func (' ' : chs) n = [] : func chs (n - 1)
func ('\n' : chs) n = [] : func chs (n - 1)
func [ch] n = [[ch]]
func (ch : chs) n = t : rs
                where t = (ch : r)
                      (r : rs) = func chs n

decode :: String -> Integer
decode [] = 0
decode (ch : chs) = 10 * decode(chs) + (chi ch - chi '0')

readInt = (decode . reverse)

funcReverse x y = func y x

parseString n = (map readInt) . (funcReverse n)

-- function to check if for a given bn and a n, as well as an array of as (already reversed), we can complete an array of bs

checkB :: Integer -> Integer -> [Integer] -> Bool
checkB bn 0 as = True
checkB 0 n as = False
checkB bn n (a : as)  | (a == bn) = checkB (bn - 1) n (a : as)
                      | (a /= bn) = checkB (bn - 1) (n - 1) (as)

-- For a given n and as (already reversed), as well as a power of 2 and current estimation, returns the B we're looking for

findB :: Integer -> [Integer] -> Integer -> Integer -> Integer
findB n vs 0 r = r
findB n vs pas 0 = 0
findB n vs pas r | (checkB (r - pas) n vs == True) = findB n vs (pas `quot` 2) (r - pas)
                 | otherwise = findB n vs (pas `quot` 2) (r)

solve :: Integer -> [Integer] -> Integer
solve n vs = findB n (reverse vs) 1073741824 1073741824

_Solve :: String -> String -> Integer
_Solve line1 line2 = (solve n as)
                where
                      n = (parseString 1 line1) !! 0
                      as = (parseString n line2)

iterateSolve :: [String] -> [Integer]

iterateSolve [] = []

iterateSolve (line1 : line2 : lines) = (_Solve line1 line2) : (iterateSolve lines)

func2 0 f = []
func2 t f = f : f : (func2 (t - 2) f)

main :: IO ()

main = do
    line <- getLine
    let t = (parseString 1 line)!!0

    contents <- replicateM (fromInteger (2 * t)) getLine
    let answer = iterateSolve contents

    mapM_ (putStrLn.show) answer
