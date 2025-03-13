#[allow(unused)]
#[allow(dead_code)]

use std::rc::Rc;

enum Atom {
    Bigonal(BigonalAtom),
    Trigonal(TrigonalAtom),
}

struct BigonalAtom {
    a: Option<Rc<Atom>>,
    b: Option<Rc<Atom>>,
}

struct TrigonalAtom {
    a: Option<Rc<Atom>>,
    b: Option<Rc<Atom>>,
    c: Option<Rc<Atom>>,
}

fn main() {
    println!("Hello, world!");
}
