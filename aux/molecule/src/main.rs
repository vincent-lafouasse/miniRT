#[allow(unused)]
#[allow(dead_code)]
use std::rc::Rc;

enum AtomKind {
    Hydrogen,
    Carbon,
    Oxygen,
    Nitrogen,
}

impl AtomKind {
    // picometers
    fn covalent_radius(&self) -> f32 {
        use AtomKind::*;
        match self {
            Hydrogen => 31.0,
            Carbon => 73.0, // varies by hybridization but this value should be fine
            Oxygen => 66.0,
            Nitrogen => 71.0,
        }
    }
}

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
