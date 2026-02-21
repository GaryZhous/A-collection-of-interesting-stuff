use std::cell::RefCell;
use std::collections::{BTreeSet, HashMap};

type Shop = i32;
type Movie = i32;
type Price = i32;

#[derive(Clone)]
struct MovieRentingSystem {
    // price[(shop, movie)] = price
    price: HashMap<(Shop, Movie), Price>,

    // available[movie] = sorted set of (price, shop) for unrented copies
    available: RefCell<HashMap<Movie, BTreeSet<(Price, Shop)>>>,

    // rented = sorted set of (price, shop, movie)
    rented: RefCell<BTreeSet<(Price, Shop, Movie)>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MovieRentingSystem {
    fn new(_n: i32, entries: Vec<Vec<i32>>) -> Self {
        let mut price = HashMap::new();
        let mut avail_map: HashMap<Movie, BTreeSet<(Price, Shop)>> = HashMap::new();

        for e in entries {
            let shop = e[0];
            let movie = e[1];
            let p = e[2];

            price.insert((shop, movie), p);
            avail_map.entry(movie).or_default().insert((p, shop));
        }

        Self {
            price,
            available: RefCell::new(avail_map),
            rented: RefCell::new(BTreeSet::new()),
        }
    }

    fn search(&self, movie: i32) -> Vec<i32> {
        let avail = self.available.borrow();
        let Some(set) = avail.get(&movie) else { return vec![] };

        set.iter().take(5).map(|&(_p, shop)| shop).collect()
    }

    fn rent(&self, shop: i32, movie: i32) {
        let p = *self.price.get(&(shop, movie)).unwrap();

        // remove from available[movie]
        {
            let mut avail = self.available.borrow_mut();
            if let Some(set) = avail.get_mut(&movie) {
                set.remove(&(p, shop));
            }
        }

        // add to rented
        self.rented.borrow_mut().insert((p, shop, movie));
    }

    fn drop(&self, shop: i32, movie: i32) {
        let p = *self.price.get(&(shop, movie)).unwrap();

        // remove from rented
        self.rented.borrow_mut().remove(&(p, shop, movie));

        // add back to available[movie]
        let mut avail = self.available.borrow_mut();
        avail.entry(movie).or_default().insert((p, shop));
    }

    fn report(&self) -> Vec<Vec<i32>> {
        let rented = self.rented.borrow();
        rented
            .iter()
            .take(5)
            .map(|&(_p, shop, movie)| vec![shop, movie])
            .collect()
    }
}
