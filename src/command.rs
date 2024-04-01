use std::cell::RefCell;
use std::rc::Rc;

mod add;
pub use add::AddCommand;

pub use super::receiver::Receiver;

/// Declares a method for executing (and undoing) a command.
///
/// Each command receives an application context to access
/// visual components (e.g. edit view) and a clipboard.
pub trait Command {
    fn execute(&mut self);
    fn undo(&mut self, node: Rc<RefCell<Receiver>>);
}
