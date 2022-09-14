use anyhow::Result;
use regex::Regex;
use std::io::{self, Read};

fn get_front_matter(text: &mut String) -> String {
    let re = Regex::new(r"(?s)^---\n(.*?)\n---").unwrap();

    let cap_opt = re.captures(text);
    let front_matter = if let Some(cap) = cap_opt {
        cap.get(1).unwrap().as_str().to_string()
    } else {
        "".to_string()
    };

    *text = re.replace(text, "").to_string();

    front_matter
}

fn read_file<R: Read>(reader: &mut R) -> Result<String> {
    let mut buf = String::new();
    reader.read_to_string(&mut buf)?;
    Ok(buf)
}

fn main() -> Result<()> {
    println!("invert to valid markdown style");

    let mut stdin = io::stdin();
    let mut text = read_file(&mut stdin)?;

    let front_matter = get_front_matter(&mut text);
    println!("front matter: \n{}", front_matter);
    println!("~~~~~~~~~~");
    println!("text: \n{}", text);

    Ok(())
}
