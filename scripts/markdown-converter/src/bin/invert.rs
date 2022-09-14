use anyhow::Result;
use std::io::{self, Read};

fn read_file<R: Read>(reader: &mut R) -> Result<String> {
    let mut buf = String::new();
    reader.read_to_string(&mut buf)?;
    Ok(buf)
}

fn main() -> Result<()> {
    println!("invert to valid markdown style");

    let mut stdin = io::stdin();
    let text = read_file(&mut stdin)?;
    println!("{}", text);

    Ok(())
}
