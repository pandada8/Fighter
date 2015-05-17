import os
import re
from jinja2 import Template


def parse(filename):
    resources = {}
    with open(filename) as fp:
        content = fp.read()
        pic = content.strip().split("\n")[0]
        for i, _ in re.findall(r"(^[\w\d_]+$\n(\s+[\S\s]+?\n)+)", content, re.MULTILINE):
            name, i = i.split('\n  ', 1)
            tmp = {}
            for k, v in [item.split(': ') for item in i.split("\n  ")[1:]]:
                tmp[k] = eval(v)  # wow bad taste
            resources[name] = tmp
    pic = os.path.join(os.path.split(os.path.abspath(filename))[0], pic)
    return pic, resources

p, resource = parse("resources/image/shoot.pack")
template = Template(open("resource.h.tpl").read())
sounds = [(os.path.splitext(i)[0], os.path.abspath(os.path.join("resources/sound/", i))) for i in os.listdir("resources/sound/")]
with open("resource.h", 'w') as fp:
    fp.write(template.render(pic=p, resource=list(resource.items()), sounds=sounds))
print("Gen Finished, loaded {} resources".format(len(resource)))
