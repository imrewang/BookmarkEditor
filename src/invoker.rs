use super::command::*;

pub struct Invoker {
    execute_history: Vec<Box<dyn Command>>,
    undo_history: Vec<Box<dyn Command>>,
}

impl Invoker {
    pub fn new() -> Self {
        Invoker {
            execute_history: Vec::new(),
            undo_history: Vec::new(),
        }
    }

    pub fn execute_command(&mut self, mut command: Box<dyn Command>) {
        command.execute();
        //cannot mutate immutable variable `command`
        self.execute_history.push(command);
        self.undo_history.clear(); // 执行新命令后清空撤销历史
    }

    pub fn undo_command(&mut self) {
        if let Some(mut command) = self.execute_history.pop() {
            command.undo();
            self.undo_history.push(command);
        } else {
            println!("undo_command111111");
        }
    }

    pub fn redo_command(&mut self) {
        if let Some(mut command) = self.undo_history.pop() {
            command.redo();
            self.execute_history.push(command);
        } else {
            println!("redo_command2222");
        }
    }
}
