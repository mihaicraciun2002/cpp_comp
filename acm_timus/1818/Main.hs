import Data.Char

main :: IO()

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

pow :: Integer -> Integer -> Integer

pow n 0 = 1
pow n x | (x `mod` 2 == 1) = (n * (pow n (x - 1)))
        | (x `mod` 2 == 0) = t * t
                            where t = pow n (x `quot` 2)


-- sum of current index, n, and array a

mySum :: Integer -> Integer -> [Integer] -> Integer

mySum index n [] = 0
mySum index n (a : as)  | (index == n) = 0
                        | (index < n) = (t + (mySum (index + 1) n as))
                                where t = a * (pow n (index)) * (pow (n - 1) (n - index))

_first :: (Integer, Integer) -> Integer
_first (a, b) = a
_second :: (Integer, Integer) -> Integer
_second (a, b) = b

euclid :: Integer -> Integer -> (Integer, Integer)
euclid 1 0 = (1, 0)
euclid a b = ((_second t), ((_first t) - c * (_second t)))
                where c = (a `quot` b)
                      r = (a `mod` b)
                      t = euclid b r

_replaceZero :: Bool -> Integer -> Integer -> Integer
_replaceZero False x y = x
_replaceZero True x y = y

main = do
    line <- getLine
    let n = (parseString 1 line)!!0
    line <- getLine
    let a = (parseString n line)

    let _S = (mySum 0 n a)

    let _B = (pow n n)
    let _A = (pow (n - 1) n)

    let _B1 = _first (euclid _B _A)

    let _S_MOD = (_A - (_S `mod` _A))

    let firstGuy = ((_S_MOD * _B1) `mod` _A + _A) `mod` _A

    let lastGuy = ((firstGuy * _B) + _S) `quot` _A

    putStrLn(show(_replaceZero (lastGuy == 0) lastGuy _B))
