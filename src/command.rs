mod add;
mod delete;

pub use add::{new_addcommand, AddCommand};
pub use delete::{new_deletecommand, DeleteCommand};

pub trait Command {
    fn execute(&mut self);
    fn undo(&mut self);
    fn redo(&mut self);
}

fn remove_quotes(input: &str) -> &str {
    if input.len() >= 2 && input.starts_with('"') && input.ends_with('"') {
        &input[1..input.len() - 1]
    } else {
        input
    }
}
