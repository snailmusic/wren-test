System.print("hiii :3")

class Fancy {
    i { __i }
    
    static slay() {
        if (__i == null) {
            __i = 0
        }
        System.print("slayed %(__i) times")
        __i = __i + 1
        return __i
    }

    static ninebottles(max) {
        for (i in max..1) {
            System.print("%(i) bottles of beer on the wall,\n%(i) bottles of beer!")
            System.print("Take one down, pass it around\n%(i - 1) bottles of beer on the wall!\n")
        }
    }
}

class Math {
    foreign static sex(a, b)
}

System.print("hiiii sex(3,4): %(Math.sex(3,4))")
