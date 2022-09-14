import re
import sys
import yaml


def invert(text: str) -> str:
    front_matter_match = re.search(r'(?s)^---\n(.*?)\n---', text)
    if front_matter_match != None:
        text = re.sub(r'(?s)^---\n(.*?)\n---', '', text)

    # unescape
    text = re.sub(r'\\([_\'\^\{\}\\])', r'\1', text)

    if front_matter_match != None:
        texts: list[str] = []

        front_matter = front_matter_match.group(1)
        yaml_obj = yaml.safe_load(front_matter)

        if 'title' in yaml_obj:
            title: str = yaml_obj['title']
            texts.append(f'# {title}')

        if 'date' in yaml_obj:
            date: str = yaml_obj['date']
            texts.append(f'<!--date {date}-->')

        if 'tags' in yaml_obj:
            tags: list[str] = yaml_obj['tags']
            texts.append(f'<!--tags {" ".join(tags)}-->')

        if 'links' in yaml_obj:
            links: list = yaml_obj['links']
            for link in links:
                label: str = link['label']
                url: str = link['url']
                texts.append(f'<!--links label="{label}" url={url}-->')

        text = '\n'.join(texts) + text

    return text


def main() -> None:
    text: str = sys.stdin.read()
    print(invert(text))


main()
