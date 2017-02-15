pub trait Sieve {
    type Item;

    fn get_limit(&self) -> Self::Item;
    fn get_size(&self) -> usize;
    fn contains(&self, Self::Item) -> Option<bool>;
    fn get_nth(&self, usize) -> Option<Self::Item>;
}
